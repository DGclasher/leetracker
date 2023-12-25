# LeeTracker

## Description
Track your DSA questions throughout.

## Installation
Create a `.env` file, refer to [this](./.env.example) for creating it.
### Setup database
#### Using docker
Get the [docker-compose.yml](./docker-compose.yml) and do `docker-compose up -d` to bring up the database.
#### Using preinstalled db
Create a database named `leetcode`
Execute the following
```
CREATE TABLE track_table (
	id INT PRIMARY KEY AUTO_INCREMENT,
	leetcodeUrl VARCHAR(250) NOT NULL,
	sub_date DATE NOT NULL DEFAULT (CURRENT_DATE));
```
### Install mysql cpp connector library
+ For debian and based distros
  ```
  sudo apt install libmysqlcppconn-dev -y
  ```
### Get leetracker
#### Download prebuild file
```
wget https://github.com/DGclasher/leetracker/releases/download/latest/leetracker-linux-amd64
chmod +x leetracker-linux-amd64
```
#### Compile from source
Clone the repo<br>
Execute
```
make all
```
## Usage
`show` : Shows help menu<br>
`add [url]` : Add problem url
