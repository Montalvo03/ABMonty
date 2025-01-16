#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <locale>
#include <map>
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

class CitaMedica {
    int idCita;
    int idPaciente;
    int idMedico;
    string fecha;
public:
    CitaMedica(int idCita, int idPaciente, int idMedico, string fecha)
        : idCita(idCita), idPaciente(idPaciente), idMedico(idMedico), fecha(fecha) {}

    int getIdCita() const { return idCita; }
    int getIdPaciente() const { return idPaciente; }
    int getIdMedico() const { return idMedico; }
    string getFecha() const { return fecha; }

    void mostrarDatos() const {
        cout << "ID Cita: " << idCita
            << ", ID Paciente: " << idPaciente
            << ", ID Médico: " << idMedico
            << ", Fecha: " << fecha << endl;
    }

    void editarCita(int nuevoIdPaciente, int nuevoIdMedico, const string& nuevaFecha) {
        idPaciente = nuevoIdPaciente;
        idMedico = nuevoIdMedico;
        fecha = nuevaFecha;
    }
};


class GestorHospitalario {
    vector<Medico> medicos;
    vector<Paciente> pacientes;
    vector<CitaMedica> citas;

    int calcularNuevoIDCitas() const {
        if (citas.empty()) {
            return 1;
        }
        int maxID = 0;
        for (const auto& cita : citas) {
            maxID = max(maxID, cita.getIdCita());
        }
        return maxID + 1;
    }

public:


    // Funciones de Citas Médicas
    void listarCitas() const {
        if (citas.empty()) {
            cout << "No hay citas médicas registradas.\n";
            return;
        }
        for (const auto& cita : citas)
            cita.mostrarDatos();
    }

    void agregarCita() {
        int nuevoIDCita = calcularNuevoIDCitas();
        int idPaciente, idMedico;
        string fecha;

        cout << "Introduzca ID del Paciente: ";
        cin >> idPaciente;
        cout << "Introduzca ID del Médico: ";
        cin >> idMedico;
        cout << "Introduzca la Fecha (Día-Mes-Año): ";
        cin.ignore();
        getline(cin, fecha);

        citas.emplace_back(nuevoIDCita, idPaciente, idMedico, fecha);
        cout << "Cita médica añadida con éxito. ID asignado: " << nuevoIDCita << endl;
    }

    void eliminarCita() {
        int idCita;
        cout << "Introduzca el ID de la cita a eliminar: ";
        cin >> idCita;

        for (auto it = citas.begin(); it != citas.end(); ++it) {
            if (it->getIdCita() == idCita) {
                citas.erase(it);
                cout << "Cita médica eliminada con éxito.\n";
                return;
            }
        }
        cout << "Cita médica con ID " << idCita << " no encontrada.\n";
    }

    void editarCita() {
        int idCita;
        cout << "Introduzca el ID de la cita a editar: ";
        cin >> idCita;

        for (auto& cita : citas) {
            if (cita.getIdCita() == idCita) {
                int nuevoIdPaciente, nuevoIdMedico;
                string nuevaFecha;

                cout << "Introduzca el nuevo ID del Paciente: ";
                cin >> nuevoIdPaciente;
                cout << "Introduzca el nuevo ID del Médico: ";
                cin >> nuevoIdMedico;
                cout << "Introduzca la nueva Fecha (Día-Mes-Año): ";
                cin.ignore();
                getline(cin, nuevaFecha);

                cita.editarCita(nuevoIdPaciente, nuevoIdMedico, nuevaFecha);
                cout << "Cita médica editada con éxito.\n";
                return;
            }
        }
        cout << "Cita médica con ID " << idCita << " no encontrada.\n";
    }

    // Menú de Citas Médicas
    void menuCitas() {
        int opcion;
        do {
            cout << "\n=== Menú de Citas Médicas ===\n";
            cout << "1. Listar Citas\n";
            cout << "2. Añadir Cita\n";
            cout << "3. Eliminar Cita\n";
            cout << "4. Editar Cita\n";
            cout << "5. Volver al Menú Principal\n";
            cout << "Seleccione una opción: ";
            cin >> opcion;

            switch (opcion) {
            case 1:
                listarCitas();
                break;
            case 2:
                agregarCita();
                break;
            case 3:
                eliminarCita();
                break;
            case 4:
                editarCita();
                break;
            case 5:
                cout << "Volviendo al Menú Principal...\n";
                break;
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
            }
        } while (opcion != 5);
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
                    cout << "Línea inválida en el archivo CSV de médicos, se ignorará.\n";
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

    vector<Medico*> buscarMedicoPorEspecialidad(const string& especialidad) {
        vector<Medico*> medicosEncontrados;
        string especialidadLower = especialidad;
        transform(especialidadLower.begin(), especialidadLower.end(), especialidadLower.begin(), ::tolower);

        for (auto& medico : medicos) {
            string medicoEspecialidadLower = medico.getEspecialidad();
            transform(medicoEspecialidadLower.begin(), medicoEspecialidadLower.end(), medicoEspecialidadLower.begin(), ::tolower);

            if (medicoEspecialidadLower == especialidadLower) {
                medicosEncontrados.push_back(&medico);
            }
        }
        return medicosEncontrados;
    }

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
                    cout << "Línea inválida en el archivo CSV de pacientes, se ignorará.\n";
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

    GestorHospitalario() {
        cargarMedicosDesdeCSV();
        cargarPacientesDesdeCSV();
    }

    ~GestorHospitalario() {
        guardarMedicosEnCSV();
        guardarPacientesEnCSV();
    }


    // Funciones para médicos
    void listarMedicos() const {
        if (medicos.empty()) {
            cout << "No hay médicos registrados.\n";
            return;
        }
        for (const auto& medico : medicos)
            medico.mostrarDatos();
    }

    void listarMedicosPorEspecialidad() {
        string especialidad;
        cout << "Introduzca la especialidad del médico: ";
        cin.ignore();
        getline(cin, especialidad);

        vector<Medico*> medicosEncontrados = buscarMedicoPorEspecialidad(especialidad);
        if (medicosEncontrados.empty()) {
            cout << "No se encontraron médicos con esa especialidad.\n";
        }
        else {
            cout << "Médicos con especialidad '" << especialidad << "':\n";
            for (auto medico : medicosEncontrados) {
                medico->mostrarDatos();
            }
        }
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

    // Funciones para pacientes
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
        cout << "Introduzca Historial: ";
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
                cout << "Introduzca el nueva historial (actual: " << paciente.getHistorial() << "): ";
                getline(cin, nuevoHistorial);

                paciente = Paciente(id, nuevoNombre, nuevoHistorial);
                guardarPacientesEnCSV();
                cout << "Paciente actualizado con éxito.\n";
                return;
            }
        }
        cout << "Paciente con ID " << id << " no encontrado.\n";
    }

  

    void listarPacientesConCronicas() const {
        cout << "\n=== Pacientes con Enfermedades Crónicas ===\n";
        bool encontrado = false;

        for (const auto& paciente : pacientes) {
            if (paciente.getHistorial().find("crónica") != string::npos ||
                paciente.getHistorial().find("cronica") != string::npos) {
                paciente.mostrarDatos();
                encontrado = true;
            }
        }

        if (!encontrado) {
            cout << "No se encontraron pacientes con enfermedades crónicas.\n";
        }
    }

    // Menú de médicos
    void menuMedicos() {
        int opcion;
        do {
            cout << "\n=== Menú de Médicos ===\n";
            cout << "1. Listar Médicos\n";
            cout << "2. Listar Médicos por Especialidad\n";
            cout << "3. Añadir Médico\n";
            cout << "4. Eliminar Médico\n";
            cout << "5. Editar Médico\n";
            cout << "6. Volver al Menú Principal\n";
            cout << "Seleccione una opción: ";
            cin >> opcion;

            switch (opcion) {
            case 1:
                listarMedicos();
                break;
            case 2:
                listarMedicosPorEspecialidad();
                break;
            case 3:
                agregarMedico();
                break;
            case 4:
                eliminarMedico();
                break;
            case 5:
                editarMedico();
                break;
            case 6:
                cout << "Volviendo al Menú Principal...\n";
                break;
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
            }
        } while (opcion != 6);
    }

    // Menú de pacientes
    void menuPacientes() {
        int opcion;
        do {
            cout << "\n=== Menú de Pacientes ===\n";
            cout << "(IMPORTANTE, AL AÑADIR UN PACIENTE CON UNA ENFERMEDAD CRÓNICA, ESPECIFICAR LA PALABRA cronica/crónica EN SU HISTORIAL)\n";
            cout << "1. Listar Pacientes\n";
            cout << "2. Añadir Paciente\n";
            cout << "3. Eliminar Paciente\n";
            cout << "4. Editar Paciente\n";
            cout << "5. Volver al Menú Principal\n";
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
                editarPaciente();
                break;
            case 5:
                cout << "Volviendo al Menú Principal...\n";
                break;
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
            }
        } while (opcion != 5);
    }

    // Menú reportes
    void menuReportes() {
        int opcion;
        do {
            cout << "\n=== Menú de Reportes ===\n";
            cout << "1. Pacientes con Enfermedades Crónicas\n";
            cout << "2. Pacientes Atendidos en un Rango de Fechas\n";
            cout << "3. Citas Pendientes por Médico o Especialidad\n";
            cout << "4. Volver al Menú Principal\n";
            cout << "Seleccione una opción: ";
            cin >> opcion;

            switch (opcion) {
            case 1:
                listarPacientesConCronicas();
                break;
            case 2:
                listarPacientesPorRangoDeFechas();
                break;
            case 3:
                listarCitasPendientes();
                break;
            case 4:
                cout << "Volviendo al Menú Principal...\n";
                break;
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
            }
        } while (opcion != 4);
    }

    // Menú principal
    void menuPrincipal() {
        int opcion;
        do {
            cout << "\n=== Menú Principal ===\n";
            cout << "1. Pacientes\n";
            cout << "2. Médicos\n";
            cout << "3. Citas\n";
            cout << "4. Reportes\n";
            cout << "5. Salir\n";
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
                menuCitas();
                break;
            case 4:
                menuReportes();
                break;
            case 5:
                cout << "Saliendo del programa.\n";
                break;
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
            }
        } while (opcion != 5);
    };
};


int main() {
    setlocale(LC_ALL, "Spanish");
    system("chcp 65001");
    GestorHospitalario gestor;
    gestor.menuPrincipal();

    return 0;
}
