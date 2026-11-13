WITH pizzeria_orders AS (
	SELECT pz.name, COUNT(pz.name) AS count, 'order' AS action_type
	FROM menu AS m 
		JOIN person_order AS po ON m.id = po.menu_id
		JOIN pizzeria AS pz ON pz.id = m.pizzeria_id
	GROUP BY name
	ORDER BY count DESC
),
pizzeria_visits AS (
	SELECT pz.name, COUNT(pz.name) AS count, 'visit' AS action_type
	FROM pizzeria AS pz
		JOIN person_visits AS pv ON pz.id = pv.pizzeria_id
	GROUP BY name
),
orders_visits AS (
	SELECT COALESCE(pz.name, pz.name) AS name, pzo.count AS orders_count,
        pzv.count AS visits_count, COALESCE(pzo.count + pzv.count, 0) AS total_count
	FROM pizzeria_orders AS pzo FULL JOIN pizzeria_visits AS pzv ON pzo.name = pzv.name
	FULL JOIN pizzeria AS pz ON pzv.name = pz.name
	ORDER BY total_count DESC, name
)
SELECT name, total_count FROM orders_visits;