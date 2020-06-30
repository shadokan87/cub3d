FROM debian:buster
RUN apt-get update && apt-get install -y wget php7.3-fpm php7.3-mysql php7.3-json php7.3-xmlrpc php7.3-curl php7.3-gd php7.3-xml php7.3-mbstring nginx mariadb-server expect vim
COPY ./srcs/* /root/
RUN bash ~/backup_config.sh
RUN bash ~/configure_nginx.sh
RUN bash ~/configure_php.sh
RUN bash ~/restart_mysql.sh && bash ~/configure_mysql.sh
RUN bash ~/install_wordpress.sh
CMD bash ~/start_main_container.sh
