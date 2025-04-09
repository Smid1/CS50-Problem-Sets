SELECT title FROM movies WHERE year = 2008;

SELECT birth FROM people WHERE name = "Emma Stone";

SELECT title FROM movies WHERE year >= 2018 ORDER BY title ASC;

SELECT COUNT(*) FROM movies
    JOIN ratings ON movies.id = ratings.movie_id
    WHERE rating = 10.0;

SELECT title, year FROM movies WHERE title LIKE "Harry Potter%" ORDER BY year ASC;

SELECT AVG(rating) FROM ratings
    JOIN movies ON ratings.movie_id = movies.id
    WHERE movies.year = 2012;

SELECT title, rating FROM movies
    JOIN ratings ON movies.id = ratings.movie_id
    WHERE movies.year = 2010
    ORDER BY rating DESC, title ASC;

SELECT people.name FROM people
    JOIN stars ON people.id = stars.person_id
    JOIN movies ON stars.movie_id = movies.id
    WHERE movies.title = "Toy Story";

SELECT DISTINCT people.name FROM people
    JOIN stars ON people.id = stars.person_id
    JOIN movies ON stars.movie_id = movies.id
    WHERE movies.year = 2004
    ORDER BY people.birth;

SELECT DISTINCT name FROM people
    JOIN directors ON people.id = directors.person_id
    JOIN movies ON directors.movie_id = movies.id
    JOIN ratings ON movies.id = ratings.movie_id
    WHERE rating >= 9.0;

SELECT DISTINCT title FROM movies
    JOIN ratings ON movies.id = ratings.movie_id
    JOIN stars ON movies.id = stars.movie_id
    JOIN people ON stars.person_id = people.id
    WHERE name = "Chadwick Boseman"
    ORDER BY rating DESC LIMIT 5;

SELECT title FROM movies
    JOIN stars ON movies.id = stars.movie_id
    JOIN people ON stars.person_id = people.id
    GROUP BY title
    WHERE people.name = "Bradley Cooper" AND title IN (
        SELECT title FROM movies
            JOIN stars ON movies.id = stars.movie_id
            JOIN people ON stars.person_id = people.id
            WHERE people.name = "Jennifer Lawrence"
    );

SELECT title FROM movies
    JOIN stars ON movies.id = stars.movie_id
    JOIN people ON stars.person_id = people.id
    GROUP BY title
    WHERE people.name = "Bradley Cooper" AND title IN (
        SELECT title FROM movies
            JOIN stars ON movies.id = stars.movie_id
            JOIN people ON stars.person_id = people.id
            WHERE people.name = "Jennifer Lawrence"
    );
