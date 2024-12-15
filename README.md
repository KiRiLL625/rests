**Для создания таблиц**
```sql
create table restaurants
(
    id              serial
        primary key,
    name            varchar(255) not null,
    dish_table_name varchar(255) not null
);

alter table restaurants
    owner to postgres;

create table dishes
(
    id            serial
        primary key,
    restaurant_id integer
        references restaurants,
    name          varchar(255) not null,
    price         integer
);

alter table dishes
    owner to postgres;

```

**Заполнение данными**
```sql
INSERT INTO restaurants (id, name, dish_table_name) VALUES
(1, 'First rest', 'dishes'),
(2, 'Second rest', 'dishes');
```
```sql
INSERT INTO dishes (restaurant_id, name, price) VALUES
(1, 'Spaghetti Carbonara', 12),
(1, 'Margherita Pizza', 8),
(1, 'Caesar Salad', 7),
(1, 'Lasagna', 13),
(1, 'Pepperoni Pizza', 9),
(1, 'Greek Salad', 6),
(1, 'Tiramisu', 5),
(1, 'Bruschetta', 4),
(1, 'Minestrone Soup', 6),
(2, 'Panna Cotta', 5);
```