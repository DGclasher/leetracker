#include <ctime>
#include <iomanip>
#include <string.h>
#include <iostream>
#include <mysql_driver.h>
#include "lib/env_reader.h"
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

// Function to show all data
void showAllData(sql::Connection *con)
{
    try
    {
        sql::PreparedStatement *pstmt;
        pstmt = con->prepareStatement("SELECT id,leetcodeUrl,sub_date from track_table");
        sql::ResultSet *resultSet = pstmt->executeQuery();

        int idWidth = 6;
        int urlWidth = 50;
        int dateWidth = 16;

        std::cout << std::left << std::setw(idWidth) << "ID"
                  << std::left << std::setw(urlWidth) << "URL"
                  << std::left << std::setw(dateWidth) << "Submission Date" << std::endl;
        std::cout << std::setfill('-') << std::setw(idWidth + urlWidth + dateWidth) << "" << std::setfill(' ') << std::endl;
        while (resultSet->next())
        {
            std::cout << std::left << std::setw(idWidth) << resultSet->getInt("id")
                      << std::left << std::setw(urlWidth) << resultSet->getString("leetcodeUrl")
                      << std::left << std::setw(dateWidth) << resultSet->getString("sub_date") << std::endl;
        }
        delete pstmt;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

// Function to insert data
void insertData(sql::Connection *con, const std::string &leetcodeUrl)
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
        std::cout << "Usage: " << argv[0] << " [options] [extra args]\nUse help for more" << std::endl;
        return 2;
    }
    EnvReader env_reader(".env");
    int port = std::stoi(env_reader.GetVariableName("MYSQL_PORT"));
    std::string mysql_host = env_reader.GetVariableName("MYSQL_HOST");
    std::string mysql_user = env_reader.GetVariableName("MYSQL_USER");
    std::string db_name = env_reader.GetVariableName("MYSQL_DATABASE");
    std::string db_password = env_reader.GetVariableName("MYSQL_ROOT_PASSWORD");
    if (db_name == "" || db_password == "")
    {
        std::cerr << "Need to specify MYSQL_DATABASE and MYSQL_ROOT_PASSWORD in env file" << std::endl;
        return 2;
    }
    try
    {
        sql::Connection *con = eshtablishConnection(mysql_host, port, mysql_user, db_password, db_name);
        std::string option = argv[1];
        if (option == "show")
        {
            if (argc < 3)
            {
                std::cerr << "Use show help to get more info." << std::endl;
                return 2;
            }
            if (strcmp(argv[2], "help") == 0)
            {
                std::cout << "show all : To display all data\nshow [id] : Show by id" << std::endl;
                return 0;
            }
            else if (strcmp(argv[2], "all") == 0)
            {
                showAllData(con);
                return 0;
            }
        }
        else if (option == "add")
        {
            if (argc != 3)
            {
                std::cerr << "Usage: " << argv[0] << " add [uri of problem]" << std::endl;
                return 2;
            }
            insertData(con, argv[2]);
        }
    }
    catch (sql::SQLException &e)
    {
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }
}
