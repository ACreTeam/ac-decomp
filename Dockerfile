FROM ubuntu:22.04 as build

# --- basic package installation ---
RUN apt-get update && \
    apt-get install -y \
        git \
        ninja-build \
        python3 \
        python3-pip \
        wget

# --- python package installation ---
COPY ./requirements.txt /temp/requirements.txt
COPY ./tools/ppcdis/requirements.txt /temp/tools/ppcdis/requirements.txt
RUN pip install -r /temp/requirements.txt
RUN rm -rf /temp

# --- wibo installation ---
RUN wget https://github.com/decompals/wibo/releases/latest/download/wibo
RUN install ./wibo /usr/bin
RUN rm wibo

# --- devkitpro installation ---
RUN wget https://apt.devkitpro.org/install-devkitpro-pacman
RUN chmod +x install-devkitpro-pacman
## assume yes for in-script apt commands
RUN sed -i 's/^apt-get.*$/& -y/g' install-devkitpro-pacman
## now do dkp-pacman installation
RUN ./install-devkitpro-pacman
RUN rm install-devkitpro-pacman
## workaround for a dumb WSL bug that happens with Windows Docker. if we don't do this, devkitPPC installation fails on Windows.
RUN if [ ! -e /etc/mtab ]; then ln -s /proc/self/mounts /etc/mtab; fi
## and finally, we get to install devkitPPC
RUN dkp-pacman -S devkitPPC --noconfirm

# --- stage ultralib headers ---
RUN mkdir -p /N64_SDK/ultra/usr/
RUN git clone https://github.com/decompals/ultralib.git /N64_SDK/ultra/usr/
## dockerfile does not seem to support extglob, so this monstrous command works around it to delete all of ultralib except the headers we need.
RUN cd /N64_SDK/ultra/usr/ && find -type f -maxdepth 1 -delete && find . -not -name 'include' -type d -maxdepth 1 -exec rm -r "{}" \;
## modify Gpopmtx's param member to be unsigned int
RUN sed -i 's/unsigned char	param:8;/unsigned int	param:8;/g' /N64_SDK/ultra/usr/include/PR/gbi.h

# --- set up work directory and env vars ---
RUN mkdir /ac-decomp
WORKDIR /ac-decomp
ENV PATH="/opt/devkitpro/tools/bin:/ac-decomp/tools:${PATH}"
ENV N64_SDK="/N64_SDK"
ENV DEVKITPPC="/opt/devkitpro/devkitPPC"

CMD echo 'Usage: docker run --rm -v ${PWD}:/ac-decomp ac-decomp python3 configure.py && ninja\n'\
         'See https://github.com/Prakxo/ac-decomp/blob/master/README.MD for more information'
