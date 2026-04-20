SELECT p.name, m.pizza_name, m.price, (m.price - (pd.discount/100)*m.price)::int AS discount_price, pz.name AS pizzeria_name
FROM person_order AS po
	JOIN person AS p ON po.person_id = p.id
	JOIN menu AS m ON po.menu_id = m.id
	JOIN pizzeria AS pz ON m.pizzeria_id = pz.id
	JOIN person_discounts AS pd ON pd.person_id = p.id
ORDER BY name, pizza_name;