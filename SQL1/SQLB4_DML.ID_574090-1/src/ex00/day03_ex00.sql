SELECT m.pizza_name, m.price, pz.name, pv.visit_date
FROM person_visits AS pv
	JOIN menu AS m ON pv.pizzeria_id = m.pizzeria_id
	JOIN person AS p ON pv.person_id = p.id
	JOIN pizzeria AS pz on pv.pizzeria_id = pz.id
WHERE p.name = 'Kate' AND m.price BETWEEN 800 AND 1000
ORDER BY m.pizza_name, m.price, pz.name;