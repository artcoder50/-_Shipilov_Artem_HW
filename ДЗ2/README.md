# ============================================
#  Сборка и запуск проекта "fizkat"
# ============================================

$ErrorActionPreference = "Stop"

$sources = @(
    "main.cpp",
    "API.cpp",
    "Service.cpp",
    "Inspector.cpp",
    "Units.cpp"
)

$exeName = "fizkat.exe"
$std     = "c++17"
$flags   = @("-Wall", "-Wextra", "-O2")

Write-Host ""
Write-Host "============================================" -ForegroundColor Cyan
Write-Host "  Сборка проекта fizkat" -ForegroundColor Cyan
Write-Host "============================================" -ForegroundColor Cyan
Write-Host ""

Write-Host "  Компилятор : g++"        -ForegroundColor Gray
Write-Host "  Стандарт   : $std"        -ForegroundColor Gray
Write-Host "  Флаги      : $($flags -join ' ')" -ForegroundColor Gray
Write-Host "  Источники  : $($sources -join ', ')" -ForegroundColor Gray
Write-Host "  Результат  : $exeName"   -ForegroundColor Gray
Write-Host ""

# --- Сборка ---
$compileCmd = "g++ -std=$std $($flags -join ' ') $($sources -join ' ') -o $exeName"

Write-Host "[1/2] Компиляция..." -ForegroundColor Yellow
Write-Host "      > $compileCmd" -ForegroundColor DarkGray
Write-Host ""

$sw = [System.Diagnostics.Stopwatch]::StartNew()
Invoke-Expression $compileCmd
$sw.Stop()

if ($LASTEXITCODE -ne 0) {
    Write-Host ""
    Write-Host "  [ОШИБКА] Компиляция завершилась с кодом $LASTEXITCODE" -ForegroundColor Red
    exit $LASTEXITCODE
}

Write-Host ""
Write-Host "  [OK] Сборка завершена за $([math]::Round($sw.Elapsed.TotalSeconds, 2)) c" -ForegroundColor Green
Write-Host ""

# --- Запуск ---
Write-Host "[2/2] Запуск $exeName..." -ForegroundColor Yellow
Write-Host "--------------------------------------------" -ForegroundColor DarkGray
Write-Host ""

if (-not (Test-Path ".\$exeName")) {
    Write-Host "  [ОШИБКА] Файл $exeName не найден" -ForegroundColor Red
    exit 1
}

& ".\$exeName"
$exitCode = $LASTEXITCODE

Write-Host ""
Write-Host "--------------------------------------------" -ForegroundColor DarkGray
Write-Host "  Программа завершилась с кодом: $exitCode" -ForegroundColor $(if ($exitCode -eq 0) { "Green" } else { "Red" })
Write-Host ""
