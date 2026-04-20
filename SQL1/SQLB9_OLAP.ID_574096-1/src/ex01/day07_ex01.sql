WITH p_names AS (
    SELECT name, COUNT(*) AS count_of_visits
    FROM person_visits AS pv
    INNER JOIN person AS p ON p.id = pv.person_id
    GROUP BY name
    ORDER BY count_of_visits DESC, name
)
SELECT * FROM (SELECT * FROM p_names LIMIT 4) AS output;