#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <locale>
#include <map>
#include <ctime>
using namespace std;

string obtenerFechaActual() {
    time_t t = time(0);
    struct tm* now = localtime(&t);

    char buffer[11];
    strftime(buffer, sizeof(buffer), "%d-%m-%Y", now);

    return string(buffer);
}


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
    string fechaIngreso;

public:
    Paciente(int id, string nombre, string historial, string fechaIngreso)
        : id(id), nombre(nombre), historial(historial), fechaIngreso(fechaIngreso) {}

    int getId() const { return id; }
    string getNombre() const { return nombre; }
    string getHistorial() const { return historial; }
    string getFechaIngreso() const { return fechaIngreso; }

    void setNombre(const string& nuevoNombre) { nombre = nuevoNombre; }
    void setHistorial(const string& nuevoHistorial) { historial = nuevoHistorial; }

    void mostrarDatos() const {
        cout << "ID: " << id << ", Nombre: " << nombre
            << ", Historial: " << historial
            << ", Fecha de Ingreso: " << fechaIngreso << endl;
    }

    string toCSV() const {
        return to_string(id) + "," + nombre + "," + historial + "," + fechaIngreso;
    }

    static Paciente fromCSV(const string& linea) {
        stringstream ss(linea);
        string idStr, nombre, historial, fechaIngreso;
        getline(ss, idStr, ',');
        getline(ss, nombre, ',');
        getline(ss, historial, ',');
        getline(ss, fechaIngreso, ',');

        if (idStr.empty() || nombre.empty() || historial.empty() || fechaIngreso.empty()) {
            throw invalid_argument("Paciente inválido en línea CSV");
        }

        return Paciente(stoi(idStr), nombre, historial, fechaIngreso);
    }
};


class CitaMedica {
    int idCita;
    int idPaciente;
    int idMedico;
    string fecha;
    string motivo;
    string urgencia;

public:
    CitaMedica(int idCita, int idPaciente, int idMedico, string fecha, string motivo, string urgencia)
        : idCita(idCita), idPaciente(idPaciente), idMedico(idMedico), fecha(fecha), motivo(motivo), urgencia(urgencia) {}

    int getIdCita() const { return idCita; }
    int getIdPaciente() const { return idPaciente; }
    int getIdMedico() const { return idMedico; }
    string getFecha() const { return fecha; }
    string getMotivo() const { return motivo; }
    string getUrgencia() const { return urgencia; }

    void mostrarDatos() const {
        cout << "ID Cita: " << idCita
            << ", ID Paciente: " << idPaciente
            << ", ID Médico: " << idMedico
            << ", Fecha: " << fecha
            << ", Motivo: " << motivo
            << ", Urgencia: " << urgencia << endl;
    }

    void editarCita(int nuevoIdPaciente, int nuevoIdMedico, const string& nuevaFecha, const string& nuevoMotivo, const string& nuevaUrgencia) {
        idPaciente = nuevoIdPaciente;
        idMedico = nuevoIdMedico;
        fecha = nuevaFecha;
        motivo = nuevoMotivo;
        urgencia = nuevaUrgencia;
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

    bool existeMedico(int idMedico) const {
        for (const auto& medico : medicos) {
            if (medico.getId() == idMedico) {
                return true;
            }
        }
        return false;
    }

    bool existePaciente(int idPaciente) const {
        for (const auto& paciente : pacientes) {
            if (paciente.getId() == idPaciente) {
                return true;
            }
        }
        return false;
    }

public:

    // Funciones de Citas Médicas
    void listarCitas() const {
        if (citas.empty()) {
            cout << "No hay citas médicas registradas.\n";
            return;
        }

        cout << "\n=== Listado de Citas Médicas ===\n";
        for (const auto& cita : citas) {
            cita.mostrarDatos();
        }
    }

    void agregarCita() {
        int nuevoIDCita = calcularNuevoIDCitas();
        int idPaciente, idMedico;
        string fecha, motivo, urgencia;

        cout << "Introduzca ID del Paciente: ";
        cin >> idPaciente;
        if (!existePaciente(idPaciente)) {
            cout << "Error: El ID del paciente no existe. Intente de nuevo.\n";
            return;
        }

        cout << "Introduzca ID del Médico: ";
        cin >> idMedico;
        if (!existeMedico(idMedico)) {
            cout << "Error: El ID del médico no existe. Intente de nuevo.\n";
            return;
        }

        cout << "Introduzca la Fecha (Día-Mes-Año): ";
        cin.ignore();
        getline(cin, fecha);
        cout << "Introduzca el Motivo de la Cita: ";
        getline(cin, motivo);

        int opcionUrgencia;
        do {
            cout << "Seleccione la Urgencia (1: Alta, 2: Media, 3: Baja): ";
            cin >> opcionUrgencia;
            switch (opcionUrgencia) {
            case 1: urgencia = "Alta"; break;
            case 2: urgencia = "Media"; break;
            case 3: urgencia = "Baja"; break;
            default: cout << "Opción no válida. Intente de nuevo.\n";
            }
        } while (opcionUrgencia < 1 || opcionUrgencia > 3);

        citas.emplace_back(nuevoIDCita, idPaciente, idMedico, fecha, motivo, urgencia);
        guardarCitasEnCSV();
        cout << "Cita médica añadida con éxito. ID asignado: " << nuevoIDCita << endl;
    }

    void eliminarCita() {
        int idCita;
        cout << "Introduzca el ID de la cita a eliminar: ";
        cin >> idCita;

        for (auto it = citas.begin(); it != citas.end(); ++it) {
            if (it->getIdCita() == idCita) {
                citas.erase(it);
                guardarCitasEnCSV();
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
                string nuevaFecha, nuevoMotivo, nuevaUrgencia;

                cout << "Introduzca el nuevo ID del Paciente: ";
                cin >> nuevoIdPaciente;
                cout << "Introduzca el nuevo ID del Médico: ";
                cin >> nuevoIdMedico;
                cout << "Introduzca la nueva Fecha (Día-Mes-Año): ";
                cin.ignore();
                getline(cin, nuevaFecha);
                cout << "Introduzca el nuevo Motivo de la Cita: ";
                getline(cin, nuevoMotivo);

                int opcionUrgencia;
                do {
                    cout << "Seleccione la nueva Urgencia (1: Alta, 2: Media, 3: Baja): ";
                    cin >> opcionUrgencia;
                    switch (opcionUrgencia) {
                    case 1: nuevaUrgencia = "Alta"; break;
                    case 2: nuevaUrgencia = "Media"; break;
                    case 3: nuevaUrgencia = "Baja"; break;
                    default: cout << "Opción no válida. Intente de nuevo.\n";
                    }
                } while (opcionUrgencia < 1 || opcionUrgencia > 3);

                cita.editarCita(nuevoIdPaciente, nuevoIdMedico, nuevaFecha, nuevoMotivo, nuevaUrgencia);
                guardarCitasEnCSV();
                cout << "Cita médica editada con éxito.\n";
                return;
            }
        }
        cout << "Cita médica con ID " << idCita << " no encontrada.\n";
    }

    void listarCitasPendientes() {
        string fechaActual = obtenerFechaActual();
        int opcion;

        cout << "\nSeleccione el criterio de búsqueda:\n";
        cout << "1. Por Médico\n2. Por Especialidad\nOpción: ";
        cin >> opcion;

        if (opcion == 1) {
            int idMedico;
            cout << "\nIntroduzca el ID del Médico: ";
            cin >> idMedico;

            cout << "\n=== Citas Pendientes para el Médico ID " << idMedico << " (Fecha actual: " << fechaActual << ") ===\n";
            bool encontrado = false;

            for (const auto& cita : citas) {
                if (cita.getIdMedico() == idMedico && cita.getFecha() >= fechaActual) {
                    cita.mostrarDatos();
                    encontrado = true;
                }
            }

            if (!encontrado) {
                cout << "No se encontraron citas pendientes para este médico.\n";
            }
        }
        else if (opcion == 2) {
            string especialidad;
            cout << "\nIntroduzca la Especialidad: ";
            cin.ignore();
            getline(cin, especialidad);

            cout << "\n=== Citas Pendientes para la Especialidad '" << especialidad << "' (Fecha actual: " << fechaActual << ") ===\n";
            bool encontrado = false;

            for (const auto& medico : medicos) {
                if (medico.getEspecialidad() == especialidad) {
                    for (const auto& cita : citas) {
                        if (cita.getIdMedico() == medico.getId() && cita.getFecha() >= fechaActual) {
                            cita.mostrarDatos();
                            encontrado = true;
                        }
                    }
                }
            }

            if (!encontrado) {
                cout << "No se encontraron citas pendientes para esta especialidad.\n";
            }
        }
        else {
            cout << "\nOpción no válida.\n";
        }
    }

    void ordenarCitasPorFecha() {
        string fechaActual = obtenerFechaActual();

        cout << "\n=== Citas ordenadas por fecha desde " << fechaActual << " ===\n";

        // Filtrar citas desde la fecha actual en adelante
        vector<CitaMedica> citasFuturas;
        for (const auto& cita : citas) {
            if (cita.getFecha() >= fechaActual) {
                citasFuturas.push_back(cita);
            }
        }

        // Ordenar las citas por fecha
        sort(citasFuturas.begin(), citasFuturas.end(), [](const CitaMedica& a, const CitaMedica& b) {
            return a.getFecha() < b.getFecha();
            });

        // Mostrar las citas ordenadas
        if (citasFuturas.empty()) {
            cout << "No hay citas futuras registradas.\n";
        }
        else {
            for (const auto& cita : citasFuturas) {
                cita.mostrarDatos();
            }
        }
    }

    void ordenarCitasPorUrgencia() {
        cout << "\n=== Citas ordenadas por urgencia ===\n";

        // Ordenar las citas por urgencia: Alta > Media > Baja
        sort(citas.begin(), citas.end(), [](const CitaMedica& a, const CitaMedica& b) {
            map<string, int> prioridad = { {"Alta", 1}, {"Media", 2}, {"Baja", 3} };
            return prioridad[a.getUrgencia()] < prioridad[b.getUrgencia()];
            });

        // Mostrar las citas ordenadas
        if (citas.empty()) {
            cout << "No hay citas registradas.\n";
        }
        else {
            for (const auto& cita : citas) {
                cita.mostrarDatos();
            }
        }
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
            cout << "5. Ordenar Citas por Fecha\n";
            cout << "6. Ordenar Citas por Urgencia\n";
            cout << "7. Volver al Menú Principal\n";
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
                ordenarCitasPorFecha();
                break;
            case 6:
                ordenarCitasPorUrgencia();
                break;
            case 7:
                cout << "Volviendo al Menú Principal...\n";
                break;
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
            }
        } while (opcion != 7);
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


    void buscarPacientePorNombre() const {
        string nombre;
        cout << "Introduzca el nombre del paciente a buscar: ";
        cin.ignore();
        getline(cin, nombre);

        bool encontrado = false;
        for (const auto& paciente : pacientes) {
            if (paciente.getNombre() == nombre) {
                paciente.mostrarDatos();
                encontrado = true;
            }
        }

        if (!encontrado) {
            cout << "No se encontró ningún paciente con el nombre especificado.\n";
        }
    }

    void buscarPacientePorFechaIngreso() const {
        string fecha;
        cout << "Introduzca la fecha de ingreso (DD-MM-AAAA): ";
        cin.ignore();
        getline(cin, fecha);

        bool encontrado = false;
        for (const auto& paciente : pacientes) {
            if (paciente.getFechaIngreso() == fecha) {
                paciente.mostrarDatos();
                encontrado = true;
            }
        }

        if (!encontrado) {
            cout << "No se encontraron pacientes con la fecha de ingreso especificada.\n";
        }
    }
public:
        // Constructor y Destructor
        GestorHospitalario() {
            cargarMedicosDesdeCSV();
            cargarPacientesDesdeCSV();
            cargarCitasDesdeCSV();
        }

        ~GestorHospitalario() {
            guardarMedicosEnCSV();
            guardarPacientesEnCSV();
            guardarCitasEnCSV();
        }


        void menuBuscarPacientes() {
            int opcion;
            do {
                cout << "\n=== Menú de Búsqueda de Pacientes ===\n";
                cout << "1. Buscar por Nombre\n";
                cout << "2. Buscar por ID\n";
                cout << "3. Buscar por Fecha de Ingreso\n";
                cout << "4. Volver al Menú de Pacientes\n";
                cout << "Seleccione una opción: ";
                cin >> opcion;

                switch (opcion) {
                case 1:
                    buscarPacientePorNombre();
                    break;
                case 2: {
                    int id;
                    cout << "Introduzca el ID del paciente a buscar: ";
                    cin >> id;
                    Paciente* paciente = buscarPacientePorID(id); // Busca al paciente por ID
                    if (paciente) {
                        paciente->mostrarDatos();
                    }
                    else {
                        cout << "No se encontró ningún paciente con el ID especificado.\n";
                    }
                    break;
                }
                case 3:
                    buscarPacientePorFechaIngreso();
                    break;
                case 4:
                    cout << "Volviendo al Menú de Pacientes...\n";
                    break;
                default:
                    cout << "Opción no válida. Intente de nuevo.\n";
                }
            } while (opcion != 4);
        }


      //Métodos para manejar citas
      void cargarCitasDesdeCSV() {
        ifstream archivo("citas.csv");
        if (!archivo) {
            ofstream nuevoArchivo("citas.csv");
            nuevoArchivo.close();
            return;
        }

        string linea;
        while (getline(archivo, linea)) {
            if (!linea.empty()) {
                stringstream ss(linea);
                string idCitaStr, idPacienteStr, idMedicoStr, fecha, motivo, urgencia;
                getline(ss, idCitaStr, ',');
                getline(ss, idPacienteStr, ',');
                getline(ss, idMedicoStr, ',');
                getline(ss, fecha, ',');
                getline(ss, motivo, ',');
                getline(ss, urgencia, ',');

                try {
                    citas.emplace_back(stoi(idCitaStr), stoi(idPacienteStr), stoi(idMedicoStr), fecha, motivo, urgencia);
                }
                catch (const invalid_argument&) {
                    cout << "Línea inválida en el archivo CSV de citas, se ignorará.\n";
                }
            }
        }
        archivo.close();
      }

      void guardarCitasEnCSV() const {
        ofstream archivo("citas.csv", ios::trunc);
        for (const auto& cita : citas) {
            archivo << cita.getIdCita() << "," << cita.getIdPaciente() << "," << cita.getIdMedico() << "," << cita.getFecha() << "," << cita.getMotivo() << "," << cita.getUrgencia() << endl;
        }
        archivo.close();
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

      void listarMedicosPorDisponibilidad() {
          string fecha;
          cout << "Introduzca la fecha (DD-MM-AAAA): ";
          cin.ignore();
          getline(cin, fecha);

          cout << "\n=== Médicos disponibles el " << fecha << " ===\n";
          bool encontrado = false;

          for (const auto& medico : medicos) {
              // Comprueba si el médico tiene alguna cita en esa fecha
              bool tieneCita = false;
              for (const auto& cita : citas) {
                  if (cita.getIdMedico() == medico.getId() && cita.getFecha() == fecha) {
                      tieneCita = true;
                      break;
                  }
              }

              // Si el médico no tiene citas ese día, lo muestra
              if (!tieneCita) {
                  medico.mostrarDatos();
                  encontrado = true;
              }
          }

          if (!encontrado) {
              cout << "No se encontraron médicos disponibles el " << fecha << ".\n";
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
        string fechaIngreso = obtenerFechaActual();

        cout << "Introduzca Nombre: ";
        cin.ignore();
        getline(cin, nombre);
        cout << "Introduzca Historial: ";
        getline(cin, historial);

        Paciente nuevoPaciente(nuevoID, nombre, historial, fechaIngreso);
         pacientes.push_back(nuevoPaciente);
        guardarPacientesEnCSV();
        cout << "Paciente añadido con éxito. ID asignado: " << nuevoID << ", Fecha de Ingreso: " << fechaIngreso << endl;
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

                //En vez de reemplazar objeto, cambiamos sus datos con los setters
                paciente.setNombre(nuevoNombre);
                paciente.setHistorial(nuevoHistorial);

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

      void listarPacientesPorRangoDeFechas() {
          string fechaInicio, fechaFin;
          cout << "\nIntroduzca la fecha de inicio (DD-MM-AAAA): ";
          cin.ignore();
          getline(cin, fechaInicio);
          cout << "Introduzca la fecha de fin (DD-MM-AAAA): ";
          getline(cin, fechaFin);

          cout << "\n=== Pacientes atendidos entre " << fechaInicio << " y " << fechaFin << " ===\n";
          bool encontrado = false;

          for (const auto& cita : citas) {
              if (cita.getFecha() >= fechaInicio && cita.getFecha() <= fechaFin) {
                  Paciente* paciente = buscarPacientePorID(cita.getIdPaciente());
                  if (paciente) {
                      paciente->mostrarDatos();
                      encontrado = true;
                  }
              }
          }

          if (!encontrado) {
              cout << "No se encontraron pacientes en el rango de fechas especificado.\n";
          }
      }

      // Menú de médicos
      void menuMedicos() {
          int opcion;
          do {
              cout << "\n=== Menú de Médicos ===\n";
              cout << "1. Listar Médicos\n";
              cout << "2. Listar Médicos por Especialidad\n";
              cout << "3. Listar Médicos por Disponibilidad\n";
              cout << "4. Añadir Médico\n";
              cout << "5. Eliminar Médico\n";
              cout << "6. Editar Médico\n";
              cout << "7. Volver al Menú Principal\n";
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
                  listarMedicosPorDisponibilidad();
                  break;
              case 4:
                  agregarMedico();
                  break;
              case 5:
                  eliminarMedico();
                  break;
              case 6:
                  editarMedico();
                  break;
              case 7:
                  cout << "Volviendo al Menú Principal...\n";
                  break;
              default:
                  cout << "Opción no válida. Intente de nuevo.\n";
              }
          } while (opcion != 7);
      }


      // Menú de pacientes
      void menuPacientes() {
          int opcion;
          do {
              cout << "\n=== Menú de Pacientes ===\n";
              cout << "1. Listar Pacientes\n";
              cout << "2. Añadir Paciente\n";
              cout << "3. Eliminar Paciente\n";
              cout << "4. Editar Paciente\n";
              cout << "5. Buscar Pacientes\n";
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
                  editarPaciente();
                  break;
              case 5:
                  menuBuscarPacientes();
                  break;
              case 6:
                  cout << "Volviendo al Menú Principal...\n";
                  break;
              default:
                  cout << "Opción no válida. Intente de nuevo.\n";
              }
          } while (opcion != 6);
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
