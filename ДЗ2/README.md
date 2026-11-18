# Запуск на Windows (PowerShell)

```powershell
g++ -std=c++17 -Wall -Wextra -O2 main.cpp API.cpp Service.cpp Inspector.cpp Units.cpp -o fizkat.exe
.\fizkat.exe
```

## Схема наследования

```text
Object (abstract)
├── Inventory (abstract)
│   ├── Helmet
│   └── ElectricItem (abstract)
│       └── Dock
└── Vehicle (abstract)
    ├── Bike
    └── ElectricVehicle (abstract)
        ├── ElectricScooter
        └── Ebike

EnergyConsumer (abstract)
├── ElectricItem
└── ElectricVehicle
```

## Умные указатели

- **`std::unique_ptr<Object>`** (`Service.hpp`, поле `items_`): парк единолично владеет каждой единицей техники. Вектор таких указателей обеспечивает полиморфное хранение и автоматическое удаление объектов при разрушении `Service`.
- **`std::shared_ptr<ModelSpec>`** (`Service.hpp`, поле `models_`): несколько единиц техники одной модели (например, два самоката `ModelX`) разделяют один общий объект `ModelSpec`. Это позволяет не дублировать данные и автоматически освобождать память, когда удаляется последняя единица этой модели.
- **`std::weak_ptr<ModelSpec>`** (`Focus.hpp`, поле `ptr_`): используется для «витрины» (`focus` / `show_focus`). `weak_ptr` не продлевает время жизни объекта. Если объект удалён (`remove`), `weak_ptr` становится `expired`, и `show_focus` выводит `expired`. Это позволяет безопасно проверять наличие объекта без риска утечек памяти.
- Другая причина, почему использованы именно они: по ТЗ.

## Исключения

Все исключения наследуются от `std::runtime_error` (`Errors.hpp`):

- **`InspectionError`** — бросается в `Inspector::checkName` (`Inspector.cpp`), если в имени объекта есть подстрока `broken` (без учёта регистра). Это штатная ситуация отказа техосмотра.
- **`ParseError`** — бросается в `Inspector::validate*` при некорректных аргументах (пустой ID, дубликат ID, отрицательная энергия, простота вне диапазона 1..10) и в `API.cpp` при ошибках разбора команд (неверное число токенов, неверный формат числа).
- **`NotFoundError`** — бросается в `Service::findById` (`Service.cpp`), если команда `focus` или `remove` ссылается на несуществующий ID.

Все проверки в `Inspector` выполняются до добавления объекта в парк. При ошибке парк не меняется.

## Шаблонная функция

В `MaxEnergy.hpp` реализована шаблонная функция:

```cpp
template<typename T>
T* mostPowerful(const std::vector<std::shared_ptr<T>>& items);
```

Она находит объект с максимальным энергопотреблением среди техники определённого типа, используя `dynamic_cast` к `EnergyConsumer`. Шаблон используется для обобщения поиска максимума, чтобы не дублировать цикл для `ElectricScooter`, `Ebike` и `Dock`.

## Использование ИИ

- написание README
- реализация функций `readCommand` и `buildMethods` в `API`
- вопросы по использованию различных систем C++
- помощь в обработке ошибок
