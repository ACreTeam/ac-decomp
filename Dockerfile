FROM ubuntu:24.04 as build

# --- basic package installation ---
RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y \
        cmake \
        git \
        ninja-build \
        python3 \
        python3-pip \
        wget

# --- python package installation ---
COPY ./requirements.txt /temp/requirements.txt
COPY ./tools/ppcdis/requirements.txt /temp/tools/ppcdis/requirements.txt
# why bother setting up a venv for this, right? ¯\_(ツ)_/¯
RUN pip install --break-system-packages -r /temp/requirements.txt
RUN rm -rf /temp

# --- wibo installation ---
RUN wget https://github.com/decompals/wibo/releases/latest/download/wibo
RUN install ./wibo /usr/bin
RUN rm wibo

# --- devkitpro installation ---
RUN wget https://apt.devkitpro.org/install-devkitpro-pacman
RUN chmod +x install-devkitpro-pacman
# assume yes for in-script apt commands
RUN sed -i 's/^apt-get.*$/& -y/g' install-devkitpro-pacman
RUN ./install-devkitpro-pacman
RUN rm install-devkitpro-pacman
# workaround for a dumb bug that happens with Windows Docker. if we don't do this, devkitPPC installation fails on Windows.
RUN if [ ! -e /etc/mtab ]; then ln -s /proc/self/mounts /etc/mtab; fi
RUN dkp-pacman -S devkitPPC --noconfirm
# dear fucking god this is hacky but it works (needed otherwise next step fails)
RUN rm /usr/bin/cpp /usr/bin/g++ /lib/cpp
# set devkitPPC executables as the default ones
RUN for file in $(find "/opt/devkitpro/devkitPPC/bin" -type f -name 'powerpc-eabi*'); do new_file=$(basename "$file" | sed 's/powerpc-eabi-//g'); update-alternatives --install "/usr/bin/$new_file" "$new_file" "$file" 0; done

# --- stage ultralib headers ---
RUN git clone https://github.com/decompals/ultralib.git /N64_SDK/ultra/usr/
# dockerfile does not seem to support extglob, so this monstrous command works around it to delete all of ultralib except the headers we need.
RUN cd /N64_SDK/ultra/usr/ && find -type f -maxdepth 1 -delete && find . -not -name 'include' -type d -maxdepth 1 -exec rm -r "{}" \;
# modify Gpopmtx's param member to be unsigned int
RUN sed -i 's/unsigned char	param:8;/unsigned int	param:8;/g' /N64_SDK/ultra/usr/include/PR/gbi.h

# --- set up work directory and env vars ---
RUN mkdir /ac-decomp
WORKDIR /ac-decomp
ENV PATH="/ac-decomp/tools:${PATH}"
ENV N64_SDK="/N64_SDK"
ENV DEVKITPPC="/opt/devkitpro/devkitPPC"

CMD echo 'Usage: docker run --rm -v ${PWD}:/ac-decomp ac-decomp python3 configure.py && python3 build.py\n'\
         'See https://github.com/Prakxo/ac-decomp/blob/master/README.MD for more information'
