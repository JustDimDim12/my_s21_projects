SELECT DISTINCT missing_date
FROM (SELECT dates::date AS missing_date, pv.person_id, pv.pizzeria_id
	FROM generate_series('2022-01-01'::date, '2022-01-10'::date, '1 day') AS dates
	LEFT JOIN person_visits AS pv
	ON dates = pv.visit_date AND person_id BETWEEN 1 AND 2)
WHERE pizzeria_id IS NULL
ORDER BY missing_date;