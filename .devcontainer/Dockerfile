FROM lagavulin16/commonapi:dev

EXPOSE 33400

COPY scripts/*.sh /tmp/scripts/
RUN find /tmp/scripts/ -type f -iname "*.sh" -exec chmod +x {} \;
RUN /bin/bash /tmp/scripts/container-set.sh