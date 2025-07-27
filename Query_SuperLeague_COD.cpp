#include <stdlib.h>
#include <iostream>
#include "stdafx.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
using namespace std;

const string server = "";
const string username = "";
const string password = "";

int main()
{
	//CONNESSIONE
    sql::Driver *driver;
    sql::Connection *con;
    sql::PreparedStatement *pstmt;
    sql::ResultSet *result;

    try
    {
        driver = get_driver_instance();
        con = driver->connect(server, username, password);
    }
    catch (sql::SQLException e)
    {
        cout << "ERROR MESSAGE: impossibile connettersi " << e.what() << endl;
        system("pause");
        exit(1);
    }

    con->setSchema("quickstartdb");

    //QUERY 1  
    pstmt = con->prepareStatement("SELECT  squadra, COUNT(squadra) AS PARTITE_GIOCATE, SUM(punteggio) AS PUNTEGGIO, SUM(FATTI) AS GF, SUM(SUBITI) AS GS, SUM(FATTI) - SUM(SUBITI) AS DIFFERENZA_RETI FROM (SELECT NOME_CLUB_CASA AS squadra, GOAL_CASA AS fatti, GOAL_TRASFERTA AS SUBITI, CASE WHEN GOAL_CASA > GOAL_TRASFERTA THEN 3 WHEN GOAL_CASA = GOAL_TRASFERTA THEN 1 ELSE 0 END punteggio FROM PARTITA UNION ALL SELECT NOME_CLUB_TRASFERTA AS squadra, GOAL_TRASFERTA AS fatti, GOAL_CASA AS SUBITI, CASE WHEN GOAL_TRASFERTA > GOAL_CASA THEN 3 WHEN GOAL_TRASFERTA = GOAL_CASA THEN 1 ELSE 0 END punteggio FROM PARTITA ) AS T GROUP BY squadra ORDER BY PUNTEGGIO DESC"); 
	result = pstmt->executeQuery();

    while (result->next())
        printf(result->getInt(1), result->getString(2).c_str(), result->getInt(3));

    delete result;
    delete pstmt;
    delete con;
    system("pause");
    return 0;

    //QUERY 2  
    pstmt = con->prepareStatement("SELECT DISTINCT GIOCATORI.NOME_CLUB, COUNT(CF) AS TOT_GIOCATORI, SUM(CASE WHEN GIOCATORI.ANNI_CONTRATTO <= '2023-30-06' THEN 1 ELSE 0 END) AS SCADENZA_2023, SUM(CASE WHEN GIOCATORI.ANNI_CONTRATTO BETWEEN '2023-07-01' AND '2024-06-30' THEN 1 ELSE 0 END) AS SCADENZA_2024, SUM(CASE WHEN GIOCATORI.ANNI_CONTRATTO BETWEEN '2024-07-01' AND '2025-06-30' THEN 1 ELSE 0 END) AS SCADENZA_2025, SUM(CASE WHEN GIOCATORI.ANNI_CONTRATTO BETWEEN '2025-07-01' AND '2026-06-30' THEN 1 ELSE 0 END) AS SCADENZA_2026, SUM(CASE WHEN GIOCATORI.ANNI_CONTRATTO BETWEEN '2026-07-01' AND '2027-06-30' THEN 1 ELSE 0 END) AS SCADENZA_2027 FROM GIOCATORI INNER JOIN CLUB ON CLUB.NOME=GIOCATORI.NOME_CLUB WHERE CLUB.NOME=GIOCATORI.NOME_CLUB GROUP BY GIOCATORI.NOME_CLUB HAVING CLUB.RUOLO = 'Fondatore' OR CLUB.RUOLO = 'Qualificato'");
    result = pstmt->executeQuery();

    while (result->next())
        printf(result->getInt(1), result->getString(2).c_str(), result->getInt(3));

    delete result;
    delete pstmt;
    delete con;
    system("pause");
    return 0;
	
    //QUERY 3  
    pstmt = con->prepareStatement("SELECT CLUB.NOME, CLUB.CAPITALE, COUNT(GIOCATORI.CF) AS TOT_GIOCATORI, SUM(GIOCATORI.VALORE_MERCATO) * 100 / CAPITALE AS VALORE_PERCENTUALE_GIOCATORI, SPONSOR.NETTO + SPONSOR.BONUS AS GUADAGNO_TOT_SPONSOR, SUM(GIOCATORI.STIPENDIO) + SUM(ALLENATORE.STIPENDIO) AS TOT_STIPENDI FROM CLUB INNER JOIN GIOCATORI ON CLUB.NOME=GIOCATORI.NOME_CLUB INNER JOIN SPONSOR ON CLUB.NOME_SPONSOR=SPONSOR.NOME INNER JOIN ALLENATORE ON CLUB.NOME=ALLENATORE.NOME_CLUB WHERE CLUB.NOME=GIOCATORI.NOME_CLUB AND CLUB.NOME_SPONSOR=SPONSOR.NOME AND CLUB.NOME=ALLENATORE.NOME_CLUB GROUP BY CLUB.NOME ORDER BY CLUB.CAPITALE DESC");
    result = pstmt->executeQuery();

    while (result->next())
        printf(result->getInt(1), result->getString(2).c_str(), result->getInt(3));

    delete result;
    delete pstmt;
    delete con;
    system("pause");
    return 0;

    //QUERY 4  
    pstmt = con->prepareStatement("SELECT NOME_CLUB, ROUND(AVG(ETA / 365), 2) AS ETA_MEDIA FROM (SELECT NOME, COGNOME, NOME_CLUB, JULIANDAY() - JULIANDAY(DATA_NASCITA) AS ETA FROM GIOCATORI) GROUP BY NOME_CLUB ORDER BY ETA_MEDIA ASC");
    result = pstmt->executeQuery();

    while (result->next())
        printf(result->getInt(1), result->getString(2).c_str(), result->getInt(3));

    delete result;
    delete pstmt;
    delete con;
    system("pause");
    return 0;
	
    //QUERY 5  
    pstmt = con->prepareStatement("SELECT CLUB.NOME, CLUB.NAZIONALITA AS NAZIONALITA_CLUB, COUNT(GIOCATORI.NAZIONALITA) AS NUMERO FROM CLUB INNER JOIN GIOCATORI ON CLUB.NOME=GIOCATORI.NOME_CLUB WHERE CLUB.NOME=GIOCATORI.NOME_CLUB AND CLUB.NAZIONALITA <> GIOCATORI.NAZIONALITA GROUP BY CLUB.NOME ORDER BY NUMERO DESC");
    result = pstmt->executeQuery();

    while (result->next())
        printf(result->getInt(1), result->getString(2).c_str(), result->getInt(3));

    delete result;
    delete pstmt;
    delete con;
    system("pause");
    return 0;
	
    //QUERY 6  
    pstmt = con->prepareStatement("SELECT EMITTENTE_TV.NOME, EMITTENTE_TV.CRONISTA, EMITTENTE_TV.OPINIONISTA, COUNT(DISTINCT PARTITA.NOME_CLUB_CASA) AS SQUADRE_COMMENTATE, SUM(PARTITA.GOAL_CASA) + SUM(PARTITA.GOAL_TRASFERTA) AS TOT_GOAL FROM EMITTENTE_TV INNER JOIN PARTITA ON EMITTENTE_TV.NOME=PARTITA.NOME_TV WHERE EMITTENTE_TV.NOME=PARTITA.NOME_TV GROUP BY PARTITA.NOME_TV ORDER BY TOT_GOAL DESC");
    result = pstmt->executeQuery();

    while (result->next())
        printf(result->getInt(1), result->getString(2).c_str(), result->getInt(3));

    delete result;
    delete pstmt;
    delete con;
    system("pause");
    return 0;
}
