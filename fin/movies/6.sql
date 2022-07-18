SELECT AVG(rating) FROM ratings JOIN movies
WHERE movies.id = ratings.movie_id AND movies.year = 2012;