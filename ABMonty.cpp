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

    void agregarMedico(const Medico& medico) {
        medicos.push_back(medico);
    }

    void agregarCita(const CitaMedica& cita) {
        citas.push_back(cita);
    }

    void agregarServicio(const Servicio& servicio) {
        servicios.push_back(servicio);
    }

    void listarPacientes() const {
        for (const auto& paciente : pacientes)
            paciente.mostrarDatos();
    }

    void listarMedicos() const {
        for (const auto& medico : medicos)
            medico.mostrarDatos();
    }

    void listarCitas() const {
        for (const auto& cita : citas)
            cita.mostrarDatos();
    }

    void listarServicios() const {
        for (const auto& servicio : servicios)
            servicio.mostrarDatos();
    }
};

int main() {
    GestorHospitalario gestor;

    gestor.agregarPaciente(Paciente(1, "Juan Perez", "Sin alergias"));
    gestor.agregarMedico(Medico(1, "Dra. Maria Lopez", "Cardiología"));
    gestor.agregarCita(CitaMedica(1, Paciente(1, "Juan Perez", "Sin alergias"),
        Medico(1, "Dra. Maria Lopez", "Cardiología"), "2024-12-04"));
    gestor.agregarServicio(Servicio(1, "Radiografía", "Diagnóstico por imagen"));

    int opcion = 0;

    do {
        cout << "\n=== Menú de Opciones ===\n";
        cout << "1. Listar Pacientes\n";
        cout << "2. Listar Médicos\n";
        cout << "3. Listar Citas Médicas\n";
        cout << "4. Listar Servicios\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cout << "\nPacientes registrados:\n";
            gestor.listarPacientes();
            break;
        case 2:
            cout << "\nMédicos registrados:\n";
            gestor.listarMedicos();
            break;
        case 3:
            cout << "\nCitas médicas registradas:\n";
            gestor.listarCitas();
            break;
        case 4:
            cout << "\nServicios disponibles:\n";
            gestor.listarServicios();
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
