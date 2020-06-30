expect ~/mysql_secure.exp
echo "CREATE DATABASE ftserver;
CREATE USER 'ftserver'@'localhost' IDENTIFIED BY 'test';
GRANT ALL PRIVILEGES ON ftserver.* TO ftserver@localhost;
FLUSH PRIVILEGES;" | mysql -u root
