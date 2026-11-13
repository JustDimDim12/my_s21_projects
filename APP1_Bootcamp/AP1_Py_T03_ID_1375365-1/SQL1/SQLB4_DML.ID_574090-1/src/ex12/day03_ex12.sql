WITH menu_id AS (
    SELECT id FROM menu WHERE pizza_name = 'greek pizza'
),
max_id AS (
    SELECT MAX(id) AS max_id FROM person_order
),
new_ids AS (
    SELECT generate_series(
        (SELECT max_id + 1 FROM max_id),
        (SELECT max_id + (SELECT COUNT(*) FROM person) FROM max_id)
    ) AS id
)
INSERT INTO person_order (id, person_id, menu_id, order_date)
SELECT n.id, p.id, (SELECT id FROM menu_id), '2022-02-25'
FROM person p
CROSS JOIN new_ids n
WHERE n.id = (SELECT max_id + p.id FROM max_id);