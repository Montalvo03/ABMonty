#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Paciente {
    int id;
    string nombre;
    string historial;
public:
    Paciente(int id, string nombre, string historial)
        : id(id), nombre(nombre), historial(historial) {}

    int getId() const { return id; }
    string getNombre() const { return nombre; }
    string getHistorial() const { return historial; }

    void mostrarDatos() const {
        cout << "ID: " << id << ", Nombre: " << nombre
            << ", Historial: " << historial << endl;
    }
};

class Medico {
    int id;
    string nombre;
    string especialidad;
public:
    Medico(int id, string nombre, string especialidad)
        : id(id), nombre(nombre), especialidad(especialidad) {}

    int getId() const { return id; }
    string getNombre() const { return nombre; }
    string getEspecialidad() const { return especialidad; }

    void mostrarDatos() const {
        cout << "ID: " << id << ", Nombre: " << nombre
            << ", Especialidad: " << especialidad << endl;
    }
};

class CitaMedica {
    int id;
    Paciente paciente;
    Medico medico;
    string fecha;
public:
    CitaMedica(int id, const Paciente& paciente, const Medico& medico, string fecha)
        : id(id), paciente(paciente), medico(medico), fecha(fecha) {}

    int getId() const { return id; }
    string getFecha() const { return fecha; }

    void mostrarDatos() const {
        cout << "ID: " << id << ", Paciente: " << paciente.getNombre()
            << ", Medico: " << medico.getNombre() << ", Fecha: " << fecha << endl;
    }
};

class Servicio {
    int id;
    string nombre;
    string descripcion;
public:
    Servicio(int id, string nombre, string descripcion)
        : id(id), nombre(nombre), descripcion(descripcion) {}

    int getId() const { return id; }
    string getNombre() const { return nombre; }
    string getDescripcion() const { return descripcion; }

    void mostrarDatos() const {
        cout << "ID: " << id << ", Nombre: " << nombre
            << ", Descripcion: " << descripcion << endl;
    }
};

class GestorHospitalario {
    vector<Paciente> pacientes;
    vector<Medico> medicos;
    vector<CitaMedica> citas;
    vector<Servicio> servicios;
public:
    void agregarPaciente(const Paciente& paciente) {
        pacientes.push_back(paciente);
    }

    void eliminarPaciente(int id) {
        for (auto it = pacientes.begin(); it != pacientes.end(); ++it) {
            if (it->getId() == id) {
                pacientes.erase(it);
                cout << "Paciente eliminado con éxito.\n";
                return;
            }
        }
        cout << "Paciente con ID " << id << " no encontrado.\n";
    }

    void listarPacientes() const {
        if (pacientes.empty()) {
            cout << "No hay pacientes registrados.\n";
            return;
        }
        for (const auto& paciente : pacientes)
            paciente.mostrarDatos();
    }

    void menuPacientes() {
        int opcion;
        do {
            cout << "\n=== Menú de Pacientes ===\n";
            cout << "1. Listar Pacientes\n";
            cout << "2. Añadir Paciente\n";
            cout << "3. Eliminar Paciente\n";
            cout << "4. Volver al menú principal\n";
            cout << "Seleccione una opción: ";
            cin >> opcion;

            switch (opcion) {
            case 1:
                listarPacientes();
                break;
            case 2: {
                int id;
                string nombre, historial;
                cout << "Introduzca ID: ";
                cin >> id;
                cout << "Introduzca Nombre: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Introduzca Historial Médico: ";
                getline(cin, historial);
                agregarPaciente(Paciente(id, nombre, historial));
                cout << "Paciente añadido con éxito.\n";
                break;
            }
            case 3: {
                int id;
                cout << "Introduzca el ID del paciente a eliminar: ";
                cin >> id;
                eliminarPaciente(id);
                break;
            }
            case 4:
                cout << "Volviendo al menú principal...\n";
                break;
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
            }
        } while (opcion != 4);
    }

    void agregarMedico(const Medico& medico) {
        medicos.push_back(medico);
    }

    void eliminarMedico(int id) {
        for (auto it = medicos.begin(); it != medicos.end(); ++it) {
            if (it->getId() == id) {
                medicos.erase(it);
                cout << "Médico eliminado con éxito.\n";
                return;
            }
        }
        cout << "Médico con ID " << id << " no encontrado.\n";
    }

    void listarMedicos() const {
        if (medicos.empty()) {
            cout << "No hay médicos registrados.\n";
            return;
        }
        for (const auto& medico : medicos)
            medico.mostrarDatos();
    }

    void menuMedicos() {
        int opcion;
        do {
            cout << "\n=== Menú de Médicos ===\n";
            cout << "1. Listar Médicos\n";
            cout << "2. Añadir Médico\n";
            cout << "3. Eliminar Médico\n";
            cout << "4. Volver al menú principal\n";
            cout << "Seleccione una opción: ";
            cin >> opcion;

            switch (opcion) {
            case 1:
                listarMedicos();
                break;
            case 2: {
                int id;
                string nombre, especialidad;
                cout << "Introduzca ID: ";
                cin >> id;
                cout << "Introduzca Nombre: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Introduzca Especialidad: ";
                getline(cin, especialidad);
                agregarMedico(Medico(id, nombre, especialidad));
                cout << "Médico añadido con éxito.\n";
                break;
            }
            case 3: {
                int id;
                cout << "Introduzca el ID del médico a eliminar: ";
                cin >> id;
                eliminarMedico(id);
                break;
            }
            case 4:
                cout << "Volviendo al menú principal...\n";
                break;
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
            }
        } while (opcion != 4);
    }
};

int main() {
    GestorHospitalario gestor;

    int opcion = 0;

    do {
        cout << "\n=== Menú Principal ===\n";
        cout << "1. Pacientes\n";
        cout << "2. Médicos\n";
        cout << "3. Citas Médicas\n";
        cout << "4. Servicios\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            gestor.menuPacientes();
            break;
        case 2:
            gestor.menuMedicos();
            break;
        case 5:
            cout << "Saliendo del programa.\n";
            break;
        default:
            cout << "Opción no válida. Intente de nuevo.\n";
        }
    } while (opcion != 5);

    return 0;
}
