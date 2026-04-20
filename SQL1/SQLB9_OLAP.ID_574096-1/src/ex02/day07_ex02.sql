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
)
(SELECT * FROM pizzeria_orders LIMIT 3)
UNION
(SELECT * FROM pizzeria_visits LIMIT 3)
ORDER BY action_type, count DESC;