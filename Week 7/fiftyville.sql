-- Log of SQL queries used to solve the mystery.

-- ANSWERS:
-- The THIEF is: Bruce
-- The city the thief ESCAPED TO: New York (LaGuardia Airport)
-- The ACCOMPLICE is: Robin

-- Getting case details based on information given
SELECT description
    FROM crime_scene_reports
    WHERE month = 7 AND day = 28 AND street = 'Humphrey Street';

-- Witnesses interviews
SELECT * FROM interviews
    WHERE transcript LIKE '%bakery%';

-- Seeing bakery security logs to see who left around crime time frame, interview 1
SELECT hour, minute, activity, license_plate
    FROM bakery_security_logs
    WHERE day = 28 AND month = 7 AND year = 2024 AND hour = 10;

-- Seeing atm transactions from that day with persons data matching bakery exiting plates, interview 2
SELECT DISTINCT people.name, people.license_plate FROM people
    JOIN bank_accounts ON people.id = bank_accounts.person_id
    JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
    JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
    WHERE
        atm_transactions.day = 28 AND
        atm_transactions.month = 7 AND
        atm_transactions.year = 2024 AND
        atm_transactions.atm_location = "Leggett Street" AND
        atm_transactions.transaction_type = "withdraw" AND
        people.license_plate IN (
            SELECT license_plate
                FROM bakery_security_logs
                WHERE day = 28 AND month = 7 AND year = 2024 AND hour = 10 AND activity = "exit"
        );

-- Seeing phone calls from that day < 1 minute duration and with people names on the list from top
SELECT people.name, caller, receiver  FROM phone_calls
    JOIN people ON phone_calls.caller = people.phone_number
    WHERE caller IN (
        SELECT DISTINCT people.phone_number FROM people
            JOIN bank_accounts ON people.id = bank_accounts.person_id
            JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
            JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
            WHERE
                atm_transactions.day = 28 AND
                atm_transactions.month = 7 AND
                atm_transactions.year = 2024 AND
                atm_transactions.atm_location = "Leggett Street" AND
                atm_transactions.transaction_type = "withdraw" AND
                people.license_plate IN (
                    SELECT license_plate
                        FROM bakery_security_logs
                        WHERE day = 28 AND month = 7 AND year = 2024 AND hour = 10 AND activity = "exit"
                )
    )
    AND duration < 60;

-- Taking fiftyville airports name
SELECT abbreviation FROM airports WHERE full_name LIKE "%Fiftyville%";

-- Seeing who was in a next day flight
SELECT people.name, flights.hour FROM people
    JOIN passengers ON people.passport_number = passengers.passport_number
    JOIN flights ON passengers.flight_id = flights.id
    JOIN airports ON flights.origin_airport_id = airports.id
    WHERE
        airports.abbreviation = "CSF" AND
        flights.day = 29 AND
        flights.month = 7 AND
        flights.year = 2024 AND
        people.name IN (
            SELECT people.name FROM phone_calls
                JOIN people ON phone_calls.caller = people.phone_number
                WHERE caller IN (
                    SELECT DISTINCT people.phone_number FROM people
                        JOIN bank_accounts ON people.id = bank_accounts.person_id
                        JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
                        JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
                        WHERE
                            atm_transactions.day = 28 AND
                            atm_transactions.month = 7 AND
                            atm_transactions.year = 2024 AND
                            atm_transactions.atm_location = "Leggett Street" AND
                            atm_transactions.transaction_type = "withdraw" AND
                            people.license_plate IN (
                                SELECT license_plate
                                    FROM bakery_security_logs
                                    WHERE day = 28 AND month = 7 AND year = 2024 AND hour = 10 AND activity = "exit"
                            )
                )
                AND duration < 60;
        )


-- Seeing who was in the next day first flight and in the 10 minute time frame mentioned before
SELECT people.name FROM people
    JOIN passengers ON people.passport_number = passengers.passport_number
    JOIN flights ON passengers.flight_id = flights.id
    JOIN airports ON flights.origin_airport_id = airports.id
    WHERE
        airports.abbreviation = "CSF" AND
        flights.day = 29 AND
        flights.month = 7 AND
        flights.year = 2024 AND
        flights.hour = 8 AND
        people.name IN (
            SELECT people.name FROM phone_calls
                JOIN people ON phone_calls.caller = people.phone_number
                WHERE caller IN (
                    SELECT DISTINCT people.phone_number FROM people
                        JOIN bank_accounts ON people.id = bank_accounts.person_id
                        JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
                        JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
                        WHERE
                            atm_transactions.day = 28 AND
                            atm_transactions.month = 7 AND
                            atm_transactions.year = 2024 AND
                            atm_transactions.atm_location = "Leggett Street" AND
                            atm_transactions.transaction_type = "withdraw" AND
                            people.license_plate IN (
                                SELECT license_plate
                                    FROM bakery_security_logs
                                    WHERE
                                        day = 28 AND
                                        month = 7 AND
                                        year = 2024 AND
                                        hour = 10 AND
                                        minute <= 30 AND
                                        activity = "exit"
                            )
                )
                AND duration < 60
        );

-- Finding out to what city
SELECT full_name FROM airports
    JOIN flights ON airports.id = flights.destination_airport_id
    WHERE
        flights.id = (
            SELECT flights.id FROM people
                JOIN passengers ON people.passport_number = passengers.passport_number
                JOIN flights ON passengers.flight_id = flights.id
                JOIN airports ON flights.origin_airport_id = airports.id
                WHERE
                    airports.abbreviation = "CSF" AND
                    flights.day = 29 AND
                    flights.month = 7 AND
                    flights.year = 2024 AND
                    flights.hour = 8 AND
                    people.name IN (
                        SELECT people.name FROM phone_calls
                            JOIN people ON phone_calls.caller = people.phone_number
                            WHERE caller IN (
                                SELECT DISTINCT people.phone_number FROM people
                                    JOIN bank_accounts ON people.id = bank_accounts.person_id
                                    JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
                                    JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
                                    WHERE
                                        atm_transactions.day = 28 AND
                                        atm_transactions.month = 7 AND
                                        atm_transactions.year = 2024 AND
                                        atm_transactions.atm_location = "Leggett Street" AND
                                        atm_transactions.transaction_type = "withdraw" AND
                                        people.license_plate IN (
                                            SELECT license_plate
                                                FROM bakery_security_logs
                                                WHERE
                                                    day = 28 AND
                                                    month = 7 AND
                                                    year = 2024 AND
                                                    hour = 10 AND
                                                    minute <= 30 AND
                                                    activity = "exit"
                                        )
                            )
                            AND duration < 60
                        )
        );

-- Finding out who the thief called to buy their tickets
SELECT name FROM people
    JOIN phone_calls ON people.phone_number = phone_calls.receiver
    WHERE caller = (
        SELECT caller
            FROM people
            JOIN phone_calls ON people.phone_number = phone_calls.caller
            WHERE name = (
                SELECT people.name FROM people
                    JOIN passengers ON people.passport_number = passengers.passport_number
                    JOIN flights ON passengers.flight_id = flights.id
                    JOIN airports ON flights.origin_airport_id = airports.id
                    WHERE
                        airports.abbreviation = "CSF" AND
                        flights.day = 29 AND
                        flights.month = 7 AND
                        flights.year = 2024 AND
                        flights.hour = 8 AND
                        people.name IN (
                            SELECT people.name FROM phone_calls
                                JOIN people ON phone_calls.caller = people.phone_number
                                WHERE caller IN (
                                    SELECT DISTINCT people.phone_number FROM people
                                        JOIN bank_accounts ON people.id = bank_accounts.person_id
                                        JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
                                        JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
                                        WHERE
                                            atm_transactions.day = 28 AND
                                            atm_transactions.month = 7 AND
                                            atm_transactions.year = 2024 AND
                                            atm_transactions.atm_location = "Leggett Street" AND
                                            atm_transactions.transaction_type = "withdraw" AND
                                            people.license_plate IN (
                                                SELECT license_plate
                                                    FROM bakery_security_logs
                                                    WHERE
                                                        day = 28 AND
                                                        month = 7 AND
                                                        year = 2024 AND
                                                        hour = 10 AND
                                                        minute <= 30 AND
                                                        activity = "exit"
                                            )
                                )
                                AND duration < 60
                        )
            )
    ) AND
    day = 28 AND
    month = 7 AND
    year = 2024 AND
    duration < 60;

