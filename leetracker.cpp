#include <ctime>
#include <iostream>
#include "env_reader.h"
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

sql::Connection *eshtablishConnection(std::string hostname, int port, std::string db_user, std::string db_password, std::string db_name)
{
    sql::mysql::MySQL_Driver *driver;
    driver = sql::mysql::get_mysql_driver_instance();
    sql::Connection *con;
    std::string mysql_uri = "tcp://" + hostname + ":" + std::to_string(port);
    con = driver->connect(mysql_uri, db_user, db_password);
    con->setSchema(db_name);
    return con;
}

void insertData(sql::Connection *con, const std::string &leetcodeUrl, const std::string db_name)
{
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    std::string time_now = std::to_string(now->tm_mday) + "-" + std::to_string(now->tm_mon + 1) + "-" + std::to_string(now->tm_year + 1900);
    
    sql::PreparedStatement *pstmt;
    pstmt = con->prepareStatement("INSERT INTO track_table (leetcodeUrl) VALUES (?)");
    pstmt->setString(1, leetcodeUrl);
    pstmt->execute();

    delete pstmt;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " [uri of problem] [env file name (default .env)]" << std::endl;
        return 2;
    }
    std::string env_file_name;
    env_file_name = argv[2] ? argv[2] : ".env";
    EnvReader env_reader(env_file_name);
    std::string db_name = env_reader.GetVariableName("MYSQL_DATABASE");
    std::string db_password = env_reader.GetVariableName("MYSQL_ROOT_PASSWORD");
    if (db_name == "" || db_password == "")
    {
        std::cerr << "Need to specify MYSQL_DATABASE and MYSQL_ROOT_PASSWORD in env file" << std::endl;
        return 2;
    }
    try
    {
        sql::Connection *con = eshtablishConnection("localhost", 3307, "root", db_password, db_name);
        std::string leetcodeUrl = argv[1];
        insertData(con, leetcodeUrl, db_name);
    }
    catch (sql::SQLException &e)
    {
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }
}