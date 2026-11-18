# ФизКат — консольный учёт парка

## Запуск на Windows (PowerShell)

g++ -std=c++17 -Wall -Wextra -O2 main.cpp API.cpp Service.cpp Inspector.cpp Units.cpp -o fizkat.exe
.\fizkat.exe

## Схема наследования

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

## Умные указатели

- std::unique_ptr<Object> (Service.hpp, поле items_): парк единолично владеет каждой единицей техники. Вектор таких указателей обеспечивает полиморфное хранение и автоматическое удаление объектов при разрушении Service.
- std::shared_ptr<ModelSpec> (Service.hpp, поле models_): несколько единиц техники одной модели (например, два самоката ModelX) разделяют один общий объект ModelSpec. Это позволяет не дублировать данные и автоматически освобождать память, когда удаляется последняя единица этой модели.
- std::weak_ptr<ModelSpec> (Focus.hpp, поле ptr_): используется для «витрины» (focus / show_focus). weak_ptr не продлевает время жизни объекта. Если объект удалён (remove), weak_ptr становится expired, и show_focus выводит expired. Это позволяет безопасно проверять наличие объекта без риска утечек памяти.
- Другая причина, почему использованы именно они: по ТЗ.

## Исключения

Все исключения наследуются от std::runtime_error (Errors.hpp):

- InspectionError — бросается в Inspector::checkName (Inspector.cpp), если в имени объекта есть подстрока broken (без учёта регистра). Это штатная ситуация отказа техосмотра.
- ParseError — бросается в Inspector::validate* при некорректных аргументах (пустой ID, дубликат ID, отрицательная энергия, простота вне диапазона 1..10) и в API.cpp при ошибках разбора команд (неверное число токенов, неверный формат числа, неизвестный тип в max).
- NotFoundError — бросается в Service::findById (Service.cpp), если команда focus или remove ссылается на несуществующий ID; а также в команде max, если в парке нет устройств запрошенного типа.

Все проверки в Inspector выполняются до добавления объекта в парк. При ошибке парк не меняется.

## Шаблонная функция

В MaxEnergy.hpp реализована шаблонная функция:

template<typename T>
T* mostPowerful(const std::vector<std::shared_ptr<T>>& items);

Она находит объект с максимальным энергопотреблением среди техники определённого типа, используя dynamic_cast к EnergyConsumer. Шаблон используется для обобщения поиска максимума, чтобы не дублировать цикл для ElectricScooter, Ebike и Dock.

## Команды

Все команды вводятся в одну строку через пробел. Регистр команд — строчный.

| Команда | Аргументы | Описание |
|---|---|---|
| add scooter | `<id> <name> <energy> <score>` | Добавить электросамокат. energy — суточное энергопотребление (double >= 0), score — простота для новичка (целое 1..10). |
| add bike | `<id> <name> <score>` | Добавить обычный велосипед (энергию не потребляет, в сумме энергии даёт 0). |
| add ebike | `<id> <name> <energy> <score>` | Добавить электровелосипед. |
| add helmet | `<id> <name>` | Добавить шлем (вещь на балансе, без энергии и «новичка»). |
| add dock | `<id> <name> <energy>` | Добавить док-станцию (вещь, потребляет энергию). |
| energy | — | Напечатать суммарное суточное энергопотребление парка (один double, 1 знак после запятой). |
| novice | — | Список прокатной техники для новичков (простота >= 6): по одной строке `<id> <name>`. |
| list | — | Все позиции баланса, отсортированные по инвентарному номеру. |
| focus | `<id>` | Установить «витрину» на позицию парка (weak_ptr на ModelSpec). |
| show_focus | — | Показать текущую витрину или expired, если объект удалён. |
| remove | `<id>` | Убрать позицию из парка. |
| models | — | Напечатать все известные модели (ModelSpec) с их score и energy. |
| max | `<type>` | Вывести самое энергоёмкое устройство указанного типа (scooter, ebike, dock). Печатает `<id> <name> <energy>`. Если устройств нет — `error: no such devices`. |
| quit | — | Завершить работу программы. |

### Пример

Ввод:
add scooter S-1 ModelX 2.5 8
add bike B-1 City 4
add scooter S-2 brokenX 1.0 9
add helmet H-1 Pro
add dock D-1 Hub 10.0
list
novice
energy
max scooter
max dock
quit

Вывод:
error: inspection rejected B-1 City
D-1 Hub
H-1 Pro
S-1 ModelX
S-1 ModelX
12.5
S-1 ModelX 2.5
D-1 Hub 10.0

Пояснения:
- add scooter S-2 brokenX ... отклонён техосмотром (в имени есть broken), в парк не попал.
- list печатает принятые позиции, отсортированные по id.
- novice выводит только прокатную технику с простотой >= 6 (в примере — S-1; велосипед B-1 с простотой 4 не попадает).
- energy = 2.5 + 0 + 10.0 = 12.5.
- max scooter выбирает среди самокатов (S-1), max dock — среди док-станций (D-1). Если устройств нужного типа нет, выводится error: no such devices.

## Использование ИИ

- написание README
- реализация функций readCommand и buildMethods в API
- вопросы по использованию различных систем C++
- помощь в обработке ошибок
- выравнивание
