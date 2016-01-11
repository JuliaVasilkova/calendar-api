
# calendar-api

## Сервис "Календарь"

### Краткое описание
Сервис предоставляет возможность вести календарь событий: добавлять и просматривать события.

#### Ресурс системы

Ресурс системы - это событие в календаре, вида:

```
{
    "eventID": "Go to gim",
    "rase_at": "YYYY-MM-DD HH:MM:SS",
}
```
rase_at - время, в которое событие произойдет

### Запросы в систему

#### GET hostname/events

Получить список событий на сегодняшнюю дату

####Пример запроса в систему

http GET http://localhost/events

####Пример ответа
```
{
    "today_events": [
        {
            "event_name": "important_event",
            "event_date": "2016-01-12 21:40:01"
        },
        {
            "event_name": "important_event",
            "event_date": "2016-01-12 19:40:01"
        }
    ]
}
```

#### PUT hostname/events/ "event_info"

Создать событие в календаре

####Пример запроса в систему

http PUT http://localhost/events event_name=important_event event_date="2016-01-12 19:40:01"

####Пример ответа

```
{
    "event_date": "2016-01-12 19:40:01", 
    "event_name": "important_event"
}

```

#### Get hostname/events/event_name

Получить событие по имени

####Пример запроса в систему

http GET http://localhost/events/important_event

####Пример ответа

```
{
    "event_date": "2016-01-12 21:40:01", 
    "event_name": "important_event"
}

```
