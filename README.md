# calendar-api

## Сервис "Календарь"

### Краткое описание
Сервис предоставляет возможность вести календарь событий: добавлять, редактировать, удалять.
Время используется в формате UTC

#### Ресурс системы

Ресурс системы - это список в календаре, вида:

```
{
    "event": "Go to gim",
    "event_id": "GUID"
    "rase_at": "YYYY-MM-DD HH:MM:SS",
    "remind_at": "YYYY-MM-DD HH:MM:SS",
}
```
rase_at - время, в которое событие произойдет
remind_at - время, в которе надо напомнить о предсоящем событии

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

#### DELETE /calendar-api/events/(event_id)

Удалить событие в календаре

```
{
    "event": "Go to gim",
    "event_id": "GUID"
    "rase_at": "YYYY-MM-DD HH:MM:SS",
    "remind_at": "YYYY-MM-DD HH:MM:SS",
}
```
