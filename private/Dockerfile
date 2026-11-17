FROM debian

# Update & upgrade APT registry.

RUN apt-get update && apt-get upgrade -y

COPY ./ ./src

# Expose those ports for debugging purposes.

EXPOSE 8081/tcp
EXPOSE 8081/udp

# EOF
