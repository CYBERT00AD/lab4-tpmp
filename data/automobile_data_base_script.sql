-- Created by Redgate Data Modeler (https://datamodeler.redgate-platform.com)
-- Last modification date: 2026-05-25 16:40:43.013

-- tables
-- Table: AUTOPARK_CONFIG
CREATE TABLE AUTOPARK_CONFIG (
    id integer NOT NULL CONSTRAINT AUTOPARK_CONFIG_pk PRIMARY KEY,
    driver_percent real
);

-- Table: AUTOPARK_DRIVERS
CREATE TABLE AUTOPARK_DRIVERS (
    id integer NOT NULL CONSTRAINT AUTOPARK_DRIVERS_pk PRIMARY KEY,
    employee_no text,
    last_name text,
    category text,
    experience integer,
    address text,
    birth_year integer,
    AUTOPARK_VECHICLES_id integer NOT NULL,
    CONSTRAINT emploee_no UNIQUE (employee_no),
    CONSTRAINT AUTOPARK_DRIVERS_AUTOPARK_VECHICLES FOREIGN KEY (AUTOPARK_VECHICLES_id)
    REFERENCES AUTOPARK_VEHICLES (id)
);

-- Table: AUTOPARK_ORDERS
CREATE TABLE AUTOPARK_ORDERS (
    id integer NOT NULL CONSTRAINT AUTOPARK_ORDERS_pk PRIMARY KEY,
    order_date integer,
    distance_km real,
    cargo_mass_kg real,
    price real,
    AUTOPARK_DRIVERS_id integer NOT NULL,
    AUTOPARK_VECHICLES_id integer NOT NULL,
    CONSTRAINT AUTOPARK_ORDERS_AUTOPARK_DRIVERS FOREIGN KEY (AUTOPARK_DRIVERS_id)
    REFERENCES AUTOPARK_DRIVERS (id),
    CONSTRAINT AUTOPARK_ORDERS_AUTOPARK_VECHICLES FOREIGN KEY (AUTOPARK_VECHICLES_id)
    REFERENCES AUTOPARK_VEHICLES (id)
);

-- Table: AUTOPARK_USERS
CREATE TABLE AUTOPARK_USERS (
    id integer NOT NULL CONSTRAINT AUTOPARK_USERS_pk PRIMARY KEY,
    login text,
    password text,
    role text,
    AUTOPARK_DRIVERS_id integer NOT NULL,
    CONSTRAINT Login UNIQUE (login),
    CONSTRAINT AUTOPARK_USERS_AUTOPARK_DRIVERS FOREIGN KEY (AUTOPARK_DRIVERS_id)
    REFERENCES AUTOPARK_DRIVERS (id)
);

-- Table: AUTOPARK_VEHICLES
CREATE TABLE AUTOPARK_VEHICLES (
    id integer NOT NULL CONSTRAINT AUTOPARK_VEHICLES_pk PRIMARY KEY,
    plate_no text,
    brand text,
    mileage_at_purchase integer,
    capacity_kg real,
    CONSTRAINT PLATE_number UNIQUE (plate_no)
);

-- End of file.

