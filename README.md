# Datamazon

Plataforma de comercio electrónico desarrollada en C++/CLI con Windows Forms, diseñada como proyecto académico para la UPC. Implementa estructuras de datos avanzadas (Listas Doblemente Enlazadas, Pilas, Colas, Árboles BST, Grafos) y algoritmos de ordenamiento (Quick Sort, Merge Sort, Heap Sort) y búsqueda de caminos (Dijkstra).

## Requisitos

- Windows 10/11
- Visual Studio 2022+ con carga de trabajo **Desarrollo para escritorio con C++** y soporte **C++/CLI**
- .NET Framework 4.7.2

## Compilación y Ejecución

1. Abrir `Datamazon.slnx` en Visual Studio.
2. Seleccionar configuración `Debug | x64`.
3. Presionar `Ctrl + F5` para compilar y ejecutar.

## Guía de Uso

### Inicio de Sesión

Al abrir la aplicación se muestra una pantalla de login. Existen dos modos de acceso:

#### Administrador

| Campo | Valor |
|-------|-------|
| Usuario | `admin` |
| Contraseña | `sixseven` |

El administrador tiene acceso completo al catálogo y al **Panel de Administración** (botón visible en la cabecera tras iniciar sesión).

#### Cliente

Cualquier otra combinación de usuario y contraseña inicia sesión como cliente:
- Si el nombre ya existe en `clients.txt`, se carga la sesión existente.
- Si no existe, se crea automáticamente un nuevo cliente con teléfono, dirección y membresía generados aleatoriamente (`prime` o `normal`).
- Los clientes **no** tienen acceso al Panel de Administración.

> La sesión se mantiene activa hasta cerrar la aplicación.

### Catálogo de Productos

- Navega por las tarjetas de productos con paginación (10 por página).
- Usa la **barra de búsqueda** en la cabecera para filtrar por nombre en tiempo real.
- Usa el **panel de filtros** lateral izquierdo para filtrar por categoría, rango de precio y criterio de ordenamiento.

#### Algoritmos de Ordenamiento

| Criterio | Algoritmo |
|----------|-----------|
| Nombre: A - Z | Quick Sort |
| Nombre: Z - A | Quick Sort |
| Precio: Menor a Mayor | Merge Sort |
| Precio: Mayor a Menor | Merge Sort |
| Stock: Menor a Mayor | Heap Sort |
| Stock: Mayor a Menor | Heap Sort |

### Carrito de Compras

- Presiona el botón **Carrito** en la cabecera para abrir/cerrar el panel deslizante.
- El carrito funciona como una **Pila (Stack - LIFO)**: el último producto agregado es el primero en eliminarse.
- Puedes aplicar un **cupón de descuento** antes de proceder al despacho.

#### Cupones Disponibles

| Código | Descuento |
|--------|-----------|
| `UPC20` | 20% |
| `DATAMAZON` | 15% |
| `PRO10` | 10% |
| `SAVE5` | 5% |

> Escribe el código en el campo "Cupon de Descuento" dentro del carrito y presiona "Aplicar".

### Despacho y Logística (GPS)

Al presionar **"Proceder al Despacho"**, se abre el mapa de rutas:
1. Selecciona una ciudad de destino en el combo.
2. Presiona **"Despachar Camion"**.
3. El sistema calcula la ruta más corta usando el **algoritmo de Dijkstra** y anima el recorrido del camión.
4. Al finalizar el recorrido se muestra un **comprobante** con la boleta de venta y la guía de remisión.

El comprobante incluye:
- Detalle de los productos comprados
- Descuento por cupón (si fue aplicado)
- Descuento Prime del 5% (si el cliente tiene membresía `prime`)
- IGV del 18%
- Código de seguimiento y ruta óptima del envío

### Panel de Administración

Accesible únicamente como **administrador**. Contiene las siguientes pestañas:

| Pestaña | Descripción |
|---------|-------------|
| Gestión Inventario | CRUD de productos con imagen, DataGridView |
| Benchmarks | Comparación de rendimiento entre estructuras |
| Estructuras | Visualización gráfica de DoubleList, Stack, Queue, BST, Graph |
| Clientes Registrados | Tabla de todos los clientes del sistema |
| Proveedores | Tabla de proveedores cargados desde `suppliers.txt` |
| Almacenes | Tabla de almacenes cargados desde `warehouses.txt` |

### Generación de Dataset

Desde la pestaña de **Gestión Inventario** en el panel admin, puedes generar un dataset de prueba:
1. Ingresa la cantidad deseada de productos en el campo.
2. Presiona **"Generar Dataset"**.
3. Se crean automáticamente los archivos `products.txt`, `clients.txt`, `suppliers.txt` y `warehouses.txt`.

## Arquitectura del Proyecto

El proyecto sigue los principios de **Clean Architecture**:

```
Datamazon/
├── Domain/
│   ├── Entities/        (Product, Client, Order, Invoice, Shipment, etc.)
│   ├── Repositories/    (Interfaces: IProductRepository, IClientRepository, etc.)
│   └── Structures/      (DoubleList, Stack, Queue, BST, Graph, Node, etc.)
├── Infrastructure/
│   ├── Datasources/     (TextFileDatasource, DatasetGenerator)
│   └── Repositories/    (ProductRepository, ClientRepository, CouponRepository, etc.)
├── Application/
│   ├── UseCases/        (SearchProductUseCase, ManageCartUseCase, ProcessOrderUseCase, etc.)
│   └── UseCaseRegistry.h
└── home_screen.h / .cpp (Presentación - Windows Forms UI)
```

## Estructuras de Datos Implementadas

- **DoubleList**: Catálogo de productos, listas de clientes y proveedores
- **Stack (Pila)**: Carrito de compras (LIFO)
- **Queue (Cola)**: Cola de pedidos en proceso (FIFO)
- **BST (Árbol Binario de Búsqueda)**: Índice de reseñas por producto
- **Graph (Grafo Ponderado)**: Mapa de ciudades para el sistema de logística y despacho

## Autor

**André** — Becario Pronabec, Universidad Peruana de Ciencias Aplicadas (UPC)
