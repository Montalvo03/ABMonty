#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

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

    string toCSV() const {
        return to_string(id) + "," + nombre + "," + especialidad;
    }

    static Medico fromCSV(const string& linea) {
        stringstream ss(linea);
        string idStr, nombre, especialidad;
        getline(ss, idStr, ',');
        getline(ss, nombre, ',');
        getline(ss, especialidad, ',');

        if (idStr.empty() || nombre.empty() || especialidad.empty()) {
            throw invalid_argument("Médico inválido en línea CSV");
        }

        return Medico(stoi(idStr), nombre, especialidad);
    }
};

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

    string toCSV() const {
        return to_string(id) + "," + nombre + "," + historial;
    }

    static Paciente fromCSV(const string& linea) {
        stringstream ss(linea);
        string idStr, nombre, historial;
        getline(ss, idStr, ',');
        getline(ss, nombre, ',');
        getline(ss, historial, ',');

        if (idStr.empty() || nombre.empty() || historial.empty()) {
            throw invalid_argument("Paciente inválido en línea CSV");
        }

        return Paciente(stoi(idStr), nombre, historial);
    }
};

class GestorHospitalario {
    vector<Paciente> pacientes;
    vector<Medico> medicos;

    // Métodos para manejar pacientes
    void cargarPacientesDesdeCSV() {
        ifstream archivo("pacientes.csv");
        if (!archivo) {
            ofstream nuevoArchivo("pacientes.csv");
            nuevoArchivo.close();
            return;
        }

        string linea;
        while (getline(archivo, linea)) {
            if (!linea.empty()) {
                try {
                    pacientes.push_back(Paciente::fromCSV(linea));
                }
                catch (const invalid_argument&) {
                    cout << "Línea inválida en el archivo CSV, se ignorará.\n";
                }
            }
        }
        archivo.close();
    }

    void guardarPacientesEnCSV() const {
        ofstream archivo("pacientes.csv", ios::trunc);
        for (const auto& paciente : pacientes) {
            archivo << paciente.toCSV() << endl;
        }
        archivo.close();
    }

    int calcularNuevoIDPacientes() const {
        if (pacientes.empty()) {
            return 1;
        }
        int maxID = 0;
        for (const auto& paciente : pacientes) {
            maxID = max(maxID, paciente.getId());
        }
        return maxID + 1;
    }

    Paciente* buscarPacientePorID(int id) {
        for (auto& paciente : pacientes) {
            if (paciente.getId() == id) {
                return &paciente;
            }
        }
        return nullptr;
    }

    vector<Paciente*> buscarPacientePorNombre(const string& nombre) {
        vector<Paciente*> pacientesEncontrados;
        for (auto& paciente : pacientes) {
            if (paciente.getNombre() == nombre) {
                pacientesEncontrados.push_back(&paciente);
            }
        }
        return pacientesEncontrados;
    }

    // Métodos para manejar médicos
    void cargarMedicosDesdeCSV() {
        ifstream archivo("medicos.csv");
        if (!archivo) {
            ofstream nuevoArchivo("medicos.csv");
            nuevoArchivo.close();
            return;
        }

        string linea;
        while (getline(archivo, linea)) {
            if (!linea.empty()) {
                try {
                    medicos.push_back(Medico::fromCSV(linea));
                }
                catch (const invalid_argument&) {
                    cout << "Línea inválida en el archivo CSV, se ignorará.\n";
                }
            }
        }
        archivo.close();
    }

    void guardarMedicosEnCSV() const {
        ofstream archivo("medicos.csv", ios::trunc);
        for (const auto& medico : medicos) {
            archivo << medico.toCSV() << endl;
        }
        archivo.close();
    }

    int calcularNuevoIDMedicos() const {
        if (medicos.empty()) {
            return 1;
        }
        int maxID = 0;
        for (const auto& medico : medicos) {
            maxID = max(maxID, medico.getId());
        }
        return maxID + 1;
    }

    Medico* buscarMedicoPorID(int id) {
        for (auto& medico : medicos) {
            if (medico.getId() == id) {
                return &medico;
            }
        }
        return nullptr;
    }

    vector<Medico*> buscarMedicoPorNombre(const string& nombre) {
        vector<Medico*> medicosEncontrados;
        for (auto& medico : medicos) {
            if (medico.getNombre() == nombre) {
                medicosEncontrados.push_back(&medico);
            }
        }
        return medicosEncontrados;
    }

public:
    GestorHospitalario() {
        cargarPacientesDesdeCSV();
        cargarMedicosDesdeCSV();
    }

    ~GestorHospitalario() {
        guardarPacientesEnCSV();
        guardarMedicosEnCSV();
    }

    // Menú de pacientes
    void listarPacientes() const {
        if (pacientes.empty()) {
            cout << "No hay pacientes registrados.\n";
            return;
        }
        for (const auto& paciente : pacientes)
            paciente.mostrarDatos();
    }

    void agregarPaciente() {
        string nombre, historial;
        int nuevoID = calcularNuevoIDPacientes();

        cout << "Introduzca Nombre: ";
        cin.ignore();
        getline(cin, nombre);
        cout << "Introduzca Historial Médico: ";
        getline(cin, historial);

        pacientes.push_back(Paciente(nuevoID, nombre, historial));
        guardarPacientesEnCSV();
        cout << "Paciente añadido con éxito. ID asignado: " << nuevoID << endl;
    }

    void eliminarPaciente() {
        int id;
        cout << "Introduzca el ID del paciente a eliminar: ";
        cin >> id;

        for (auto it = pacientes.begin(); it != pacientes.end(); ++it) {
            if (it->getId() == id) {
                pacientes.erase(it);
                guardarPacientesEnCSV();
                cout << "Paciente eliminado con éxito.\n";
                return;
            }
        }
        cout << "Paciente con ID " << id << " no encontrado.\n";
    }

    void editarPaciente() {
        int id;
        cout << "Introduzca el ID del paciente a editar: ";
        cin >> id;

        for (auto& paciente : pacientes) {
            if (paciente.getId() == id) {
                string nuevoNombre, nuevoHistorial;
                cout << "Introduzca el nuevo nombre (actual: " << paciente.getNombre() << "): ";
                cin.ignore();
                getline(cin, nuevoNombre);
                cout << "Introduzca el nuevo historial (actual: " << paciente.getHistorial() << "): ";
                getline(cin, nuevoHistorial);

                paciente = Paciente(id, nuevoNombre, nuevoHistorial);
                guardarPacientesEnCSV();
                cout << "Paciente actualizado con éxito.\n";
                return;
            }
        }
        cout << "Paciente con ID " << id << " no encontrado.\n";
    }

    // Menú de médicos
    void listarMedicos() const {
        if (medicos.empty()) {
            cout << "No hay médicos registrados.\n";
            return;
        }
        for (const auto& medico : medicos)
            medico.mostrarDatos();
    }

    void agregarMedico() {
        string nombre, especialidad;
        int nuevoID = calcularNuevoIDMedicos();

        cout << "Introduzca Nombre: ";
        cin.ignore();
        getline(cin, nombre);
        cout << "Introduzca Especialidad: ";
        getline(cin, especialidad);

        medicos.push_back(Medico(nuevoID, nombre, especialidad));
        guardarMedicosEnCSV();
        cout << "Médico añadido con éxito. ID asignado: " << nuevoID << endl;
    }

    void eliminarMedico() {
        int id;
        cout << "Introduzca el ID del médico a eliminar: ";
        cin >> id;

        for (auto it = medicos.begin(); it != medicos.end(); ++it) {
            if (it->getId() == id) {
                medicos.erase(it);
                guardarMedicosEnCSV();
                cout << "Médico eliminado con éxito.\n";
                return;
            }
        }
        cout << "Médico con ID " << id << " no encontrado.\n";
    }

    void editarMedico() {
        int id;
        cout << "Introduzca el ID del médico a editar: ";
        cin >> id;

        for (auto& medico : medicos) {
            if (medico.getId() == id) {
                string nuevoNombre, nuevaEspecialidad;
                cout << "Introduzca el nuevo nombre (actual: " << medico.getNombre() << "): ";
                cin.ignore();
                getline(cin, nuevoNombre);
                cout << "Introduzca la nueva especialidad (actual: " << medico.getEspecialidad() << "): ";
                getline(cin, nuevaEspecialidad);

                medico = Medico(id, nuevoNombre, nuevaEspecialidad);
                guardarMedicosEnCSV();
                cout << "Médico actualizado con éxito.\n";
                return;
            }
        }
        cout << "Médico con ID " << id << " no encontrado.\n";
    }

    // Menú principal
    void menuPacientes() {
        int opcion;
        do {
            cout << "\n=== Menú de Pacientes ===\n";
            cout << "1. Listar Pacientes\n";
            cout << "2. Añadir Paciente\n";
            cout << "3. Eliminar Paciente\n";
            cout << "4. Buscar Paciente\n";
            cout << "5. Editar Paciente\n";
            cout << "6. Volver al Menú Principal\n";
            cout << "Seleccione una opción: ";
            cin >> opcion;

            switch (opcion) {
            case 1:
                listarPacientes();
                break;
            case 2:
                agregarPaciente();
                break;
            case 3:
                eliminarPaciente();
                break;
            case 4:
            {
                int opcionBusqueda;
                string nombreBuscar;
                cout << "¿Desea buscar por ID o Nombre? (1: ID, 2: Nombre): ";
                cin >> opcionBusqueda;

                if (opcionBusqueda == 1) {
                    int idBuscar;
                    cout << "Introduzca el ID del paciente: ";
                    cin >> idBuscar;
                    Paciente* paciente = buscarPacientePorID(idBuscar);
                    if (paciente) paciente->mostrarDatos();
                    else cout << "Paciente no encontrado.\n";
                }
                else if (opcionBusqueda == 2) {
                    cout << "Introduzca el nombre del paciente: ";
                    cin.ignore();
                    getline(cin, nombreBuscar);
                    vector<Paciente*> pacientesEncontrados = buscarPacientePorNombre(nombreBuscar);
                    if (pacientesEncontrados.empty()) {
                        cout << "No se encontraron pacientes con ese nombre.\n";
                    }
                    else {
                        for (auto paciente : pacientesEncontrados) {
                            paciente->mostrarDatos();
                        }
                    }
                }
                else {
                    cout << "Opción no válida.\n";
                }
            }
            break;
            case 5:
                editarPaciente();
                break;
            case 6:
                cout << "Volviendo al Menú Principal...\n";
                break;
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
            }
        } while (opcion != 6);
    }

    void menuMedicos() {
        int opcion;
        do {
            cout << "\n=== Menú de Médicos ===\n";
            cout << "1. Listar Médicos\n";
            cout << "2. Añadir Médico\n";
            cout << "3. Eliminar Médico\n";
            cout << "4. Editar Médico\n";
            cout << "5. Volver al Menú Principal\n";
            cout << "Seleccione una opción: ";
            cin >> opcion;

            switch (opcion) {
            case 1:
                listarMedicos();
                break;
            case 2:
                agregarMedico();
                break;
            case 3:
                eliminarMedico();
                break;
            case 4:
                editarMedico();
                break;
            case 5:
                cout << "Volviendo al Menú Principal...\n";
                break;
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
            }
        } while (opcion != 5);
    }

    void menuPrincipal() {
        int opcion;
        do {
            cout << "\n=== Menú Principal ===\n";
            cout << "1. Pacientes\n";
            cout << "2. Médicos\n";
            cout << "3. Salir\n";
            cout << "Seleccione una opción: ";
            cin >> opcion;

            switch (opcion) {
            case 1:
                menuPacientes();
                break;
            case 2:
                menuMedicos();
                break;
            case 3:
                cout << "Saliendo del programa.\n";
                break;
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
            }
        } while (opcion != 3);
    }
};

int main() {
    GestorHospitalario gestor;
    gestor.menuPrincipal();
    return 0;
}
