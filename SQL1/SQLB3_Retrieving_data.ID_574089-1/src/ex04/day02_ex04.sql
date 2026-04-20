WITH pizzas AS (SELECT * FROM menu
	WHERE pizza_name = 'mushroom pizza' OR pizza_name = 'pepperoni pizza')
SELECT p.pizza_name, pz.name AS pizzeria_name, p.price
FROM pizzas p JOIN pizzeria pz ON p.pizzeria_id = pz.id
ORDER BY pizza_name, pizzeria_name;