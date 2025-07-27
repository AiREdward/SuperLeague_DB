# 🏆 SuperLeague Database

Un database completo per la gestione di un campionato di calcio europeo con 25 squadre di élite.

## 📋 Descrizione del Progetto

Il database SuperLeague è progettato per gestire un torneo calcistico europeo che include:
- **15 squadre fondatrici** (Manchester City, Juventus, Inter, Milan, etc.)
- **5 squadre qualificate** (Roma, Benfica, RB Leipzig, etc.)
- **5 squadre non qualificate** (Napoli, Celtic, Galatasaray, etc.)

## 🗂️ Struttura del Database

### Tabelle Principali

#### 🏟️ **CLUB**
Informazioni sui club partecipanti:
- Nome, colori della maglia, nazionalità
- Presidente, anno di fondazione, trofei vinti
- Capitale finanziario, stadio di casa, sponsor principale

#### ⚽ **GIOCATORI**
Database completo dei giocatori:
- Dati anagrafici (CF, nome, cognome, data di nascita)
- Caratteristiche tecniche (ruolo, piede preferito, numero di maglia)
- Aspetti contrattuali (stipendio, scadenza contratto, valore di mercato)
- Statistiche (presenze, sponsor personale)

#### 👨‍💼 **ALLENATORE**
Informazioni sui tecnici:
- Dati personali e contrattuali
- Modulo tattico preferito e media punti

#### 🏟️ **STADIO**
Caratteristiche degli impianti:
- Capacità, anno di costruzione, proprietà, città

#### 🎮 **PARTITA**
Gestione delle partite:
- Risultati, orari, giornata di campionato
- Arbitro designato, emittente TV
- Collegamenti con club, stadio e giornata

#### 📺 **EMITTENTE_TV**
Copertura televisiva:
- Cronisti e opinionisti
- Lingua di trasmissione

#### 👨‍⚖️ **ARBITRO**
Database arbitri con dati anagrafici

#### 📅 **GIORNATA**
Calendario del campionato

#### 💰 **SPONSOR**
Contratti di sponsorizzazione con importi netti e bonus

#### 🎫 **BIGLIETTO**
Sistema di biglietteria con prezzi, tipologie e settori

## 📊 Query di Analisi Implementate

Il database include 6 query avanzate per l'analisi dei dati:

### 1. 🏆 **Classifica Generale**
Classifica completa con:
- Partite giocate
- Punti totali
- Goal fatti/subiti
- Differenza reti

### 2. 📋 **Scadenze Contrattuali**
Analisi delle scadenze contrattuali dei giocatori per club e anno

### 3. 💰 **Bilancio Club**
Analisi finanziaria completa:
- Capitale disponibile
- Valore rosa giocatori (percentuale sul capitale)
- Ricavi da sponsorizzazioni
- Costi totali stipendi

### 4. 👥 **Età Media Rosa**
Calcolo dell'età media dei giocatori per squadra

### 5. 🌍 **Diversità Nazionale**
Conteggio giocatori stranieri per club

### 6. 📺 **Statistiche TV**
Goal totali trasmessi per emittente televisiva

## 🚀 Come Utilizzare il Database

### Prerequisiti
- SQLite o qualsiasi DBMS compatibile con SQL standard
- Editor SQL (DB Browser for SQLite, phpMyAdmin, etc.)

### Installazione
1. Clona o scarica il repository
2. Importa il file `db.sql` nel tuo DBMS preferito
3. Esegui lo script per creare tabelle e popolare i dati

```sql
-- Esegui il file db.sql per creare e popolare il database
sqlite3 superleague.db < db.sql
```

### Esempi di Utilizzo

```sql
-- Visualizza la classifica attuale
SELECT squadra, PUNTEGGIO, PARTITE_GIOCATE, GF, GS, DIFFERENZA_RETI
FROM (
  SELECT squadra, COUNT(squadra) AS PARTITE_GIOCATE, SUM(punteggio) AS PUNTEGGIO, 
         SUM(FATTI) AS GF, SUM(SUBITI) AS GS, SUM(FATTI) - SUM(SUBITI) AS DIFFERENZA_RETI
  FROM (
    SELECT NOME_CLUB_CASA AS squadra, GOAL_CASA AS fatti, GOAL_TRASFERTA AS subiti,
           CASE WHEN GOAL_CASA > GOAL_TRASFERTA THEN 3
                WHEN GOAL_CASA = GOAL_TRASFERTA THEN 1 ELSE 0 END punteggio
    FROM PARTITA
    UNION ALL
    SELECT NOME_CLUB_TRASFERTA AS squadra, GOAL_TRASFERTA AS fatti, GOAL_CASA AS subiti,
           CASE WHEN GOAL_TRASFERTA > GOAL_CASA THEN 3
                WHEN GOAL_TRASFERTA = GOAL_CASA THEN 1 ELSE 0 END punteggio
    FROM PARTITA
  ) AS T
  GROUP BY squadra
) ORDER BY PUNTEGGIO DESC;

-- Trova i giocatori più pagati
SELECT NOME, COGNOME, NOME_CLUB, STIPENDIO
FROM GIOCATORI
ORDER BY STIPENDIO DESC
LIMIT 10;

-- Club con il maggior valore di mercato
SELECT NOME_CLUB, SUM(VALORE_MERCATO) as VALORE_TOTALE
FROM GIOCATORI
GROUP BY NOME_CLUB
ORDER BY VALORE_TOTALE DESC;
```

## 📈 Ottimizzazioni Performance

Il database include un indice ottimizzato per le query sui risultati:

```sql
CREATE INDEX RISULTATI
ON PARTITA(COD, GOAL_CASA, GOAL_TRASFERTA);
```

## 📋 Schema Relazionale

Il database implementa un modello relazionale normalizzato con:
- **Integrità referenziale** tramite foreign key
- **Cascading updates/deletes** per mantenere la coerenza
- **Vincoli di dominio** appropriati per ogni campo

### Diagramma ER
Le principali relazioni del database:
- CLUB ← GIOCATORI (1:N)
- CLUB ← ALLENATORE (1:1)
- CLUB → STADIO (N:1)
- CLUB → SPONSOR (N:1)
- PARTITA → CLUB (casa/trasferta)
- PARTITA → ARBITRO (N:1)
- PARTITA → EMITTENTE_TV (N:1)

## 🔧 Tecnologie Utilizzate

- **SQL** - Linguaggio di query
- **SQLite** - Database engine (compatibile con MySQL, PostgreSQL)
- **Modello ER** - Progettazione concettuale

## 📁 Struttura File

```
SuperLeague_DB/
├── db.sql              # Script principale del database
├── README.md           # Documentazione del progetto
└── Relazione.pdf       # Documentazione tecnica dettagliata
```

## 🏆 Squadre Partecipanti

### Squadre Fondatrici (15)
- **Premier League**: Manchester City, Manchester United, Chelsea, Arsenal, Liverpool, Tottenham
- **Serie A**: Juventus, Inter, Milan
- **La Liga**: Real Madrid, Barcelona, Atlético Madrid
- **Bundesliga**: Bayern Monaco, Borussia Dortmund
- **Ligue 1**: PSG

### Squadre Qualificate (5)
- Roma (Serie A)
- Benfica (Primeira Liga)
- RB Leipzig (Bundesliga)
- Siviglia (La Liga)
- Ajax (Eredivisie)

### Squadre Non Qualificate (5)
- Napoli (Serie A)
- Celtic (Scottish Premiership)
- Galatasaray (Süper Lig)
- Porto (Primeira Liga)
- Olympique Lyonnais (Ligue 1)

## 🎯 Funzionalità Avanzate

- **Gestione completa tornei** con gironi e classifiche
- **Sistema di biglietteria** con prezzi variabili
- **Analisi finanziarie** approfondite
- **Statistiche televisive** dettagliate
- **Monitoraggio contratti** giocatori e staff
- **Performance tracking** per arbitri e emittenti

## 👥 Contributor

Progetto sviluppato per la gestione di un campionato calcistico europeo di élite.

## 📄 Licenza

Questo progetto è sviluppato per scopi educativi e di dimostrazione.

---

*Per maggiori informazioni tecniche, consulta il file `Relazione.pdf` incluso nel repository.*
