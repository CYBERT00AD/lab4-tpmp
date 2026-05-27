INSERT INTO AUTOPARK_CONFIG (id, driver_percent) VALUES (1, 20);

INSERT INTO AUTOPARK_VEHICLES (id, plate_no, brand, mileage_at_purchase, capacity_kg)
VALUES
(1, 'AA1111-1', 'MAZ', 120000, 5000),
(2, 'BB2222-2', 'GAZ', 90000, 3000);

INSERT INTO AUTOPARK_DRIVERS (id, employee_no, last_name, category, experience, address, birth_year, AUTOPARK_VECHICLES_id)
VALUES
(1, 'D001', 'Ivanov', 'C', 7, 'Minsk', 1988, 1),
(2, 'D002', 'Petrov', 'B', 4, 'Grodno', 1994, 2);

INSERT INTO AUTOPARK_USERS (id, login, password, role, AUTOPARK_DRIVERS_id)
VALUES
(1, 'admin', 'admin', 'admin', 1),
(2, 'driver1', '1234', 'driver', 1),
(3, 'driver2', '1234', 'driver', 2);

INSERT INTO AUTOPARK_ORDERS (id, order_date, distance_km, cargo_mass_kg, price, AUTOPARK_DRIVERS_id, AUTOPARK_VECHICLES_id)
VALUES
(1, 20260501, 120.5, 2500, 1000, 1, 1),
(2, 20260503, 80.0, 1500, 650, 2, 2),
(3, 20260505, 210.0, 3000, 1700, 1, 1);