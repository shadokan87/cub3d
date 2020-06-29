echo "CREATE DATABASE ft_server;" | mysql -u root
echo "CREATE USER 'ft_server'@'localhost' IDENTIFIED BY 'test';" | mysql -u root
echo "GRANT ALL PRIVILEGES ON ft_server.* TO ft_server@localhost;" | mysql -u root
echo "FLUSH PRIVILEGES;" | mysql -u root
