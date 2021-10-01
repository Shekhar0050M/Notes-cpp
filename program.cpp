#include <iostream>
#include <string>
#include <pqxx/pqxx>


int main()
{
    try
    {
        pqxx::connection C("dbname = input_database_name user = postgres password = input_password hostaddr = 127.0.0.1 port = 5432");
        //Check
        std::string sql = "SELECT to_regclass('public.betanotes')";
        pqxx::nontransaction N(C);
        pqxx::result R(N.exec(sql));
        pqxx::result::const_iterator c = R.begin();
        N.abort();
        pqxx::work W(C);
        if (c[0].is_null())
        {
            //Setup  start
            sql = "CREATE TABLE BETANOTES( cur_date DATE , strt_time time , TITLE VARCHAR, DESCRIPTION VARCHAR )";
            //Execution started
            W.exec(sql);
            //Commit to end and update db;
            W.commit();
            std::cout << "Created table successfully\n";
        }
        int value = 0;
        std::cout << "Click 1 to insert\nClick 2 to show all\nClick 3 to show a certain note\nClick 4 to delete a note\nEnter value:: ";
        std::cin >> value;
        switch (value)
        {
        case 1:
        {
            std::string description, title;
            std::cout << "Write your Title\n";
            std::cin >> title;
            std::cout << "Write your content:: ";
            std::cin >> description;
            sql = "INSERT INTO BETANOTES VALUES(CURRENT_DATE,CURRENT_TIME,'" + title + "','" + description + "')";
            W.exec(sql);
            W.commit();
            break;
        }
        case 2:
        {
            sql = "select * from betanotes";
            pqxx::result R(W.exec(sql));
            W.commit();
            for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c)
            {
                std::cout << "On " << c[0].as<std::string>() << " you saved " << c[3].as<std::string>() << " in " << c[2].as<std::string>() << std::endl;
            }
            break;
        }
        case 3:
        {
            int choice = 0;
            std::string date, month, year, title1;
            std::cout << "Search by date(press 1)\nSearch by month(press 2)\nSearch by year(press 3)\nSearch by title(press 4)" << std::endl;
            std::cin >> choice;
            switch (choice)
            {
            case 1:
            {
                std::cout << "Enter date:: ";
                std::cin >> date;
                sql = "SELECT * FROM BETANOTES WHERE extract(day from cur_date)=" + date;
                pqxx::result R(W.exec(sql));
                for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c)
                {
                    std::cout << "On " << c[0].as<std::string>() << " you saved " << c[3].as<std::string>() << " in " << c[2].as<std::string>() << std::endl;
                }
                std::cout << "END" << std::endl;
                break;
            }
            case 2:
            {
                std::cout << "Enter month:: ";
                std::cin >> month;
                sql = "SELECT * FROM BETANOTES WHERE extract(month from cur_date)=" + month;
                pqxx::result R(W.exec(sql));
                for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c)
                {
                    std::cout << "On " << c[0].as<std::string>() << " you saved " << c[3].as<std::string>() << " in " << c[2].as<std::string>() << std::endl;
                }
                std::cout << "END" << std::endl;
                break;
            }
            case 3:
            {
                std::cout << "Enter year:: ";
                std::cin >> year;
                sql = "SELECT * FROM BETANOTES WHERE extract(year from cur_date)=" + year;
                pqxx::result R(W.exec(sql));
                for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c)
                {
                    std::cout << "On " << c[0].as<std::string>() << " you saved " << c[3].as<std::string>() << " in " << c[2].as<std::string>() << std::endl;
                }
                std::cout << "END" << std::endl;
                break;
            }
            case 4:
            {
                std::cout << "Enter title1:: ";
                std::cin >> title1;
                sql = "SELECT * FROM BETANOTES WHERE title='" + title1 + "'";
                pqxx::result R(W.exec(sql));
                for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c)
                {
                    std::cout << "On " << c[0].as<std::string>() << " you saved " << c[3].as<std::string>() << " in " << c[2].as<std::string>() << std::endl;
                }
                std::cout << "END" << std::endl;
                break;
            }
            }
        }
        case 4:
        {
            int choice = 0;
            std::string date, month, year, title1;
            std::cout << "Delete by date(press 1)\nDelete by month(press 2)\nDelete by year(press 3)\nDelete by title(press 4)" << std::endl;
            std::cin >> choice;
            switch (choice)
            {
            case 1:
            {
                std::cout << "Enter date:: ";
                std::cin >> date;
                sql = "DELETE FROM BETANOTES WHERE extract(day from cur_date)=" + date;
                pqxx::result R(W.exec(sql));
                W.commit();
                for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c)
                {
                    std::cout << "On " << c[0].as<std::string>() << " you saved " << c[3].as<std::string>() << " in " << c[2].as<std::string>() << std::endl;
                }
                std::cout << "END" << std::endl;
                break;
            }
            case 2:
            {
                std::cout << "Enter month:: ";
                std::cin >> month;
                sql = "DELETE FROM BETANOTES WHERE extract(month from cur_date)=" + month;
                pqxx::result R(W.exec(sql));
                W.commit();
                for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c)
                {
                    std::cout << "On " << c[0].as<std::string>() << " you saved " << c[3].as<std::string>() << " in " << c[2].as<std::string>() << std::endl;
                }
                std::cout << "END" << std::endl;
                break;
            }
            case 3:
            {
                std::cout << "Enter year:: ";
                std::cin >> year;
                sql = "DELETE FROM BETANOTES WHERE extract(year from cur_date)=" + year;
                pqxx::result R(W.exec(sql));
                W.commit();
                for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c)
                {
                    std::cout << "On " << c[0].as<std::string>() << " you saved " << c[3].as<std::string>() << " in " << c[2].as<std::string>() << std::endl;
                }
                std::cout << "END" << std::endl;
                break;
            }
            case 4:
            {
                std::cout << "Enter title1:: ";
                std::cin >> title1;
                sql = "DELETE FROM BETANOTES WHERE title='" + title1 + "'";
                pqxx::result R(W.exec(sql));
                W.commit();
                for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c)
                {
                    std::cout << "On " << c[0].as<std::string>() << " you saved " << c[3].as<std::string>() << " in " << c[2].as<std::string>() << std::endl;
                }
                std::cout << "END" << std::endl;
                break;
            }
            }
        }
        }
        //Setup end
        C.disconnect();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

