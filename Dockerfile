FROM debian:buster
RUN apt-get update && apt-get install -y systemd php7.3-fpm php7.3-mysql php7.3-json php7.3-xmlrpc php7.3-curl php7.3-gd php7.3-xml php7.3-mbstring nginx mariadb-server expect vim
CMD tail -f /dev/null
