WITH miss AS (SELECT dates::date AS missing_date
	FROM generate_series('2022-01-01'::date, '2022-01-10'::date, '1 day') AS dates)
SELECT DISTINCT m.missing_date
FROM miss AS m
	LEFT JOIN person_visits AS pv
	ON m.missing_date = pv.visit_date AND person_id BETWEEN 1 AND 2
WHERE pizzeria_id IS NULL
ORDER BY missing_date;