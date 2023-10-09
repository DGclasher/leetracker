# leetracker

## Description
Track your DSA questions throughout.

## Installation
+ Create a `.env` file, refer to [this](./.env.example) for creating the `.env`.
----
#### Using docker
+ Make sure you have [docker](https://docs.docker.com/engine/install/) and [docker-compose](https://docs.docker.com/compose/install/) installed.
+ Start the container
  ```
  sudo docker-compose up -d
  ```
#### Using local mysql db
+ Login to mysql console
+ Create database `leetcode`
  ```
  CREATE DATABASE leetcode;
  ```
+ Execute the [initialize.sql](./db/initialize.sql)
----

+ Install mysqlcpp connector library (On debian and based distros)
  ```
  sudo apt install libmysqlcppconn-dev -y
  ```
+ Or install from source, follow [this](https://dev.mysql.com/doc/connector-cpp/1.1/en/connector-cpp-installation-source-unix.html).
+ Compile
  ```
  make all
  ```

## Usage
#### Showing available data
+ ```
  ./leetracker show help
  ```

#### Adding url
+ ```
  ./leetracker add [uri of problem]
  ```
