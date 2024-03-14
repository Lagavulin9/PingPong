FROM lagavulin16/vsomeip:dev

RUN apt install -y sudo

COPY scripts/*.sh /tmp/scripts/
RUN find /tmp/scripts/ -type f -iname "*.sh" -exec chmod +x {} \;
RUN /bin/bash /tmp/scripts/container-set.sh

EXPOSE 33400