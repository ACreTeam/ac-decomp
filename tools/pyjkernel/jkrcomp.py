import enum
import struct

__all__ = [
    "JKRCompression", "check_compression", "decompress", "compress",
    "decompress_szs", "compress_szs", "decompress_szp", "compress_szp"
]


class JKRCompression(enum.Enum):
    """
    A constant representing a JKernel compression format or no compression at all.
    """
    NONE = 0  # Use no compression at all
    SZP = 1   # Nintendo's older compression format used in some Nintendo 64 and GameCube games
    SZS = 2   # Nintendo's newer compression format used since GameCube games


def check_compression(data) -> JKRCompression:
    """
    Peeks at the input data's first four bytes to determine what JKernel compression format was used to compress the
    data. A constant representing the respective compression format will be returned.

    :param data: the input buffer to be inspected.
    :return: a constant representing a JKernel compression format or no compression at all.
    """
    # Magic is Ya_0
    if data[0] == 0x59 and data[1] == 0x61 and data[3] == 0x30:
        # Yaz0 -> SZS
        if data[2] == 0x7A:
            return JKRCompression.SZS
        # Yay0 -> SZP
        elif data[2] == 0x79:
            return JKRCompression.SZP

    return JKRCompression.NONE


def decompress(data) -> bytes:
    """
    Attempts to decompress the input data using JKernel decompression algorithms. If no JKernel compression format was
    detected, the input buffer will be returned again.

    :param data: the buffer to be decompressed.
    :return: a bytes object containing the decompressed data or the input buffer if no compressed data was found.
    """
    # Magic is Ya_0
    if data[0] == 0x59 and data[1] == 0x61 and data[3] == 0x30:
        # Yaz0 -> SZS
        if data[2] == 0x7A:
            return decompress_szs(data)
        # Yay0 -> SZP
        elif data[2] == 0x79:
            return __decompress_szp__(data)

    return data


def compress(data, compression: JKRCompression, level: int = 7) -> bytes:
    """
    Attempts to compress the input data using the specified JKernel compression format. If no JKernel compression format
    was detected, the input buffer will be returned again. SZP compression is not implemented yet. Therefore, attempting
    to compress a buffer with this algorithm yields a ``NotImplementedError``.

    :param data: the buffer to be compressed.
    :param compression: the compression algorithm to be used.
    :param level: the compression level (6 to 9; 6 is fastest and 9 is slowest).
    :return: a bytes object containing the compressed data or the input buffer if no compression was specified.
    """
    if compression == JKRCompression.SZS:
        return compress_szs(data, level)
    elif compression == JKRCompression.SZP:
        return compress_szp(data, level)

    return data


def decompress_szs(data) -> bytes:
    """
    Decompresses SZS-encoded input data and returns the decompressed bytes. This checks if the four magic bytes are
    equal to the string "Yaz0" to ensure that the buffer contains SZS data. The input buffer will be returned in case
    this check fails. Otherwise, the actual decompression will occur.

    :param data: the buffer to be decompressed.
    :returns: a bytes object containing the decompressed data or the input buffer if no compressed data was found.
    """
    if data[0] == 0x59 and data[1] == 0x61 and data[2] == 0x7A and data[3] == 0x30:
        raise NotImplementedError("SZS decompression is not supported yet.")

    return data


def compress_szs(data, level: int = 7) -> bytes:
    """
    Compresses the input data in the SZS compression format and returns the compressed bytes.

    :param data: the buffered data to be compressed.
    :param level: the compression level (6 to 9; 6 is fastest and 9 is slowest).
    :return: the compressed data.
    """
    raise NotImplementedError("SZS compression is not supported yet.")


def decompress_szp(data) -> bytes:
    """
    Decompresses SZP-encoded input data and returns the decompressed bytes. This checks if the four magic bytes are
    equal to the string "Yay0" to ensure that the buffer contains SZP data. The input buffer will be returned in case
    this check fails. Otherwise, the actual decompression will occur.

    :param data: the buffer to be decompressed.
    :returns: a bytes object containing the decompressed data or the input buffer if no compressed data was found.
    """
    if data[0] == 0x59 and data[1] == 0x61 and data[2] == 0x79 and data[3] == 0x30:
        return __decompress_szp__(data)

    return data


def __decompress_szp__(data) -> bytes:
    # Parse header and prepare output buffer
    decompressed_size, off_copy_table, off_chunks = struct.unpack_from(">3I", data, 0x4)
    decompressed = bytearray(decompressed_size)

    off_in = 16  # Compressed data comes after header
    off_out = 0

    block = 0    # The control block that describes how to decompress data, 32-bit
    counter = 0  # Keeps track of the remaining bits to be checked for the current control block

    while off_out < decompressed_size:
        # Get control block, which is a 32-bit word describing how to decompress data from the input buffer. Like SZS,
        # the bits are read starting from the most significant bit. If the bit is set, we copy the next byte in the byte
        # chunk table. Otherwise, we read information from the copy table to determine which decompressed bytes to copy
        # into the output buffer.
        if counter == 0:
            block = struct.unpack_from(">I", data, off_in)[0]
            counter = 32
            off_in += 4

        # Is the most significant bit set? If so, copy a plain byte into the output buffer.
        if block & 0x80000000:
            decompressed[off_out] = data[off_chunks]
            off_chunks += 1
            off_out += 1
        # Otherwise, read and copy decompressed data.
        else:
            # Read tokens
            b1 = data[off_copy_table]
            b2 = data[off_copy_table + 1]
            off_copy_table += 2

            # Get copy offset and size
            dist = ((b1 & 0xF) << 8) | b2
            off_copy = off_out - dist - 1
            len_copy = b1 >> 4

            # Copy 18+ bytes?
            if len_copy == 0:
                len_copy = data[off_chunks] + 18
                off_chunks += 1
            # Copy up to 17 bytes
            else:
                len_copy += 2

            # Copy the actual data
            for _ in range(len_copy):
                decompressed[off_out] = decompressed[off_copy]
                off_out += 1
                off_copy += 1

        # Left-shift control block and decrement remaining bits to be checked
        block <<= 1
        counter -= 1

    return bytes(decompressed)


def compress_szp(data, level: int = 7) -> bytes:
    """
    Compresses the input data in the SZP compression format and returns the compressed bytes.
    Not implemented yet.

    :param data: the buffered data to be compressed.
    :param level: the compression level.
    :return: the compressed data.
    """
    raise NotImplementedError("SZP compression is not supported yet.")
