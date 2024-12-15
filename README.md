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
    name          varchar(255)   not null,
    price         numeric(10, 2) not null
);

alter table dishes
    owner to postgres;

```