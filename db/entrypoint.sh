#!/bin/sh

if [ ! -f /var/lib/mysql/.initialized ]; then
  echo "Initializing database..."
  mysql -u root --password="$MYSQL_ROOT_PASSWORD" -D "$MYSQL_DATABASE" -P "$MYSQL_TCP_PORT" < /docker-entrypoint-initdb.d/init.sql
  touch /var/lib/mysql/.initialized
fi
