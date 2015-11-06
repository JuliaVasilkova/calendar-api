# calendar-api

## Сервис "Календарь"

### Краткое описание
Сервис предоставляет возможность вести календарь событий: добавлять, редактировать, удалять.

#### Ресурс системы

Ресурс системы - это список в календаре, вида:

```
{
    "events": [
    {
        "event": ["Feed my cat"],
        "event_id":123,
        "rase-at": "YYYY-MM-DD HH:MM:SS",
        "remind-at": "YYYY-MM-DD HH:MM:SS",
    },
    ...
    {  
        "event": ["Wash my car"],
        "event_id":124,
        "rase-at": "YYYY-MM-DD HH:MM:SS",
        "remind-at": "YYYY-MM-DD HH:MM:SS",
    },
    ...
    ]
}
```
### Запросы в систему

#### GET /calendar-api/events/(date)

Получить список событий на определенную дату

```
{
    "events": [
        {
            "event": "I have to do smth at this time",
            "event_id": "GUID"
            "rase_at": "YYYY-MM-DD HH:MM:SS",
            "remind_at": "YYYY-MM-DD HH:MM:SS",
        },
        ...
    ]
}
```
#### POST /calendar-api/events/(date)

Создать событие в календаре

```
{
    "event": "Go to gim",
    "event_id": "GUID"
    "rase_at": "YYYY-MM-DD HH:MM:SS",
    "remind_at": "YYYY-MM-DD HH:MM:SS",
}
```

#### DELETE /calendar-api/events/(date)

Удалить событие в календаре

```
{
    "event": "Go to gim",
    "event_id": "GUID"
    "rase_at": "YYYY-MM-DD HH:MM:SS",
    "remind_at": "YYYY-MM-DD HH:MM:SS",
}
```
