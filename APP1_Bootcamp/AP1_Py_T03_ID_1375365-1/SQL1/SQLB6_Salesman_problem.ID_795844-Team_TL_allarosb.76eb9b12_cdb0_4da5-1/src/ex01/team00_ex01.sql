WITH tours AS (
  SELECT w1.point1 as first,
    w1.point2 as second,
    w2.point2 as third, 
    w3.point2 as fourth,
    w4.point2 as last,
    (w1.cost + w2.cost + w3.cost + w4.cost) as total_cost
  FROM ways w1
    JOIN ways w2 ON w2.point1 = w1.point2 AND w2.point2 != 'a'
    JOIN ways w3 ON w3.point1 = w2.point2 AND w3.point2 != w2.point1 AND w3.point2 != 'a'
    JOIN ways w4 ON w4.point1 = w3.point2 AND w4.point2 = 'a'
  WHERE w1.point1 = 'a'
)
SELECT total_cost, 
  CONCAT('{', first, ',', second, ',', third, ',', fourth, ',', last, '}') AS tour
FROM tours
WHERE total_cost = (SELECT MIN(total_cost) FROM tours)
  OR total_cost = (SELECT MAX(total_cost) FROM tours)
ORDER BY total_cost, tour;