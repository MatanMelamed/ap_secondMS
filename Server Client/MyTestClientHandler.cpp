#include "MyTestClientHandler.h"

MyTestClientHandler::MyTestClientHandler(Solver<string, string> *solver,
                                         CacheManager<string, string> *manager)
        : _solver(solver), _manager(manager) {}

server_side::ClientHandler *MyTestClientHandler::Clone() {
    return new MyTestClientHandler(_solver->Clone(), _manager->Clone());
}


void MyTestClientHandler::handleClient(server_side::TCP_client clientSock) {

    // build matrix
    //SearchableMatrix matrix = GetMatrixRequest(clientSock);
    //std::string matrixString = matrix.toString();

    std::string current = clientSock.GetLine();
    std::string answer;
    while (current != END_INDICATOR) {
        std::cout << "client handler::GetLine() returned: " << current << "\n";
        answer = GetAnswer(current);
        std::cout << "client handler::GetAnswer() returned: " << answer << "\n";
        clientSock.Send(answer);
        current = clientSock.GetLine();
    }
    // ask cache and solver
}

SearchableMatrix MyTestClientHandler::GetMatrixRequest(server_side::TCP_client
                                                       client) {

    std::vector<int> matrix_data;
    int matrix_col;
    int matrix_row = 0;

    // get first line -> get number of columns
    std::string current = client.GetLine();
    StringSeparatorByComma(current, matrix_data);
    matrix_col = (int) matrix_data.size();
    ++matrix_row;

    // get all numbers including rows and exit,entrance cells.
    while (current != END_INDICATOR) {
        current = client.GetLine();
        StringSeparatorByComma(current, matrix_data);
        ++matrix_row;
    }

    // Create matrix
    matrix_row -= 2; // last two rows were entrance and exit
    SearchableMatrix matrix = SearchableMatrix(matrix_row, matrix_col);

    // Set Exit and Entrance by the 4 last numbers received.
    int last_index = (int) matrix_data.size() - 1;
    matrix.SetExitState({matrix_data[last_index], matrix_data[last_index - 1]});
    matrix.SetInitialState({matrix_data[last_index - 2],
                            matrix_data[last_index - 3]});

    // remove the 4 last numbers received
    matrix_data.pop_back();
    matrix_data.pop_back();
    matrix_data.pop_back();
    matrix_data.pop_back();

    // set the rest as data
    matrix.SetData(matrix_data);

    return matrix;
}

std::string MyTestClientHandler::GetAnswer(std::string problem) {
    std::string solution;
    if (_manager->IsSolutionExists(problem)) {
        solution = _manager->GetSolution(problem);
    } else {
        solution = _solver->solve(problem);
        _manager->SaveSolution(problem, solution);
    }
    return solution;
}

MyTestClientHandler::~MyTestClientHandler() {
    delete _solver;
    delete _manager;
}
