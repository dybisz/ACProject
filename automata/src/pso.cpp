//
// Created by dybisz on 11/12/15.
//

#include "pso.h"
#include "mcclain_rao.h"

PSO::PSO(string toolUrl, int numberOfStates, int populationFactor) :
        _tool(toolUrl),
        _psoNumberOfStates(numberOfStates),
        _numberOfSymbols(_tool.alphabet.size()),
        _populationFactor(populationFactor) {

    try {
        _loadAndLogSwarmSize();
        _loadAndLogRandomParticles(_swarmSize);
        _loadAndLogWordsGenerator(_tool.alphabet);
        _loadAndLogToolFitnessResults();
    }
    catch (std::exception &e) {
        LOG_ERROR(e.what())
    }

    _globalBestFitness = 0;
}

void PSO::_loadAndLogSwarmSize() {
    _swarmSize = _calculateSwarmSize(_psoNumberOfStates, _numberOfSymbols, _populationFactor);
    LOG_DEBUG("_swarmSize calculated: " + to_string(_swarmSize));
}

// TODO(dybisz) google test
int PSO::_calculateSwarmSize(int numberOfStates, int numberOfSymbols, int populationFactor) {
    int swarmSize = numberOfStates * numberOfSymbols * populationFactor;

    if (swarmSize < 1) {
        throw invalid_argument("swarmSize < 1");
    }

    return swarmSize;
}

void PSO::_loadAndLogRandomParticles(int numberOfParticles) {
    utils::seed();
    _particles = _generateRandomParticles(numberOfParticles);
    LOG_DEBUG(to_string(numberOfParticles) + " particles randomly generated and saved to _particles");
}

// TODO(dybisz) google test
vector<Particle *> PSO::_generateRandomParticles(int numberOfParticles) {
    vector<Particle *> particles;
    double speedFactor = 0.5;

    if (numberOfParticles < 1) {
        throw invalid_argument("numberOfParticles < 1");
    }

    for (int i = 0; i < numberOfParticles; i++) {
        Particle *p = new Particle(_psoNumberOfStates, _numberOfSymbols, speedFactor);
        particles.push_back(p);
    }
    return particles;
}

void PSO::_loadAndLogWordsGenerator(vector<int> alphabet) {
    _wordsGenerator = new WordsGenerator(alphabet);
    LOG_INFO("Pairs of Words generated");
}

void PSO::_loadAndLogToolFitnessResults() {
    _toolFitnessResults = _generateToolFitnessResults();
    LOG_INFO("Fitness function results for _tool calculated and saved.");
}

vector<int> PSO::_generateToolFitnessResults() {
    vector<int> toolFitnessResults;
    vector<PairOfWords> pairs = _wordsGenerator->getPairs();

    // TODO(dybisz) check for errors

    for (auto pair = pairs.begin(); pair != pairs.end(); ++pair) {
        bool inRelation = _tool.checkRelationInducedByLanguage((*pair).word1, (*pair).word2);
        int result = (inRelation) ? 1 : 0;
        toolFitnessResults.push_back(result);
    }

    return toolFitnessResults;
}

double PSO::_fitnessFunction(Particle *p) {
    vector<PairOfWords> pairs = _wordsGenerator->getPairs();
    double count = 0;

    for (unsigned int i = 0; i < pairs.size(); i++) {
        Word w1 = pairs[i].word1;
        Word w2 = pairs[i].word2;
        bool inRelation = p->_particleRepresentation->checkRelationInducedByLanguage(w1, w2);
        int result = (inRelation) ? 1 : 0;
        count += (result == _toolFitnessResults[i]) ? 1 : 0;
    }

    return count / (double) pairs.size();
}

void PSO::compute() {
    LOG_INFO("Particle Swarm Optimization: start computing...")
    for (int t = 0; t < MAX_ITER; t++) {

        LOG_INFO("Interation: " + to_string(t));

        // Calculate pbest using Fitness Function
        _calculatePBestAndFitness(_particles);

        // Update neighbourhood and compute lbest
        _updateNeighbourhoods();

        // Update particles positions
        _updateParticles();

        std::cout << "Global Best Fintess: " << _globalBestFitness << std::endl;
    }
    LOG_INFO("Particle Swarm Optimization: scomputing ends.")
}

void PSO::_calculatePBestAndFitness(vector<Particle *> particles) {

    for (unsigned int i = 0; i < particles.size(); i++) {
        double fitness = _fitnessFunction(particles[i]);

        if (particles[i]->bestFitness < fitness) {
            particles[i]->pbest = particles[i]->_position;
            particles[i]->bestFitness = fitness;
        }

        if (_globalBestFitness < fitness){
            _globalBestFitness = fitness;
        }
    }
}

void PSO::_updateParticles() {
    std::cout << "Particles count: " << _particles.size() << std::endl;
    for (auto particle : _particles) {
        std::cout << "Particles count: " << _particles.size() << std::endl;
        particle->update();
    }
}

/*
 * Updates the neighbourhood.
 */
void PSO::_updateNeighbourhoods() {
    LOG_INFO("Update Neighbourhood Starting");

    int start_k, end_k;
    start_k = 2;
    end_k = 20;

    // Compute cluster evaluation.
    McClainRao<double> mc_r(start_k, end_k);

    // Get vector of points from vector of particles.
    // Must preserve the indexing !!!
    vector<Point<double>*> points = _particlesToPoints(_particles);

    mc_r.compute(&points);

    // Get the most optimal clustering
    KMeans<double>* km = mc_r.getBestClustering();

    std::cout << "Neighbourhood Count: " << km->getK() << std::endl;

    // For each neighbourhood (cluster), find the lbest
    for(int c = 0; c < km->getK(); c++){
        std::vector<int> clusterIndices = km->getClusterIndices(c);

        int bestIndex = clusterIndices[0];
        double bestFitness = _particles[bestIndex]->bestFitness;

        // Find lbest
        for(unsigned int i = 0; i < clusterIndices.size(); i++){
            int index = clusterIndices[i];

            if(bestFitness < _particles[index]->bestFitness){
                bestFitness = _particles[index]->bestFitness;
                bestIndex = index;
            }
        }

        std::cout << "lbest(" << c << ") = "
            << _particles[bestIndex]->_position <<std::endl;

        // Assign lbest to each particle
        for(unsigned int i = 0; i < clusterIndices.size(); i++){
            int index = clusterIndices[i];
            _particles[index]->lbest = _particles[bestIndex]->_position;
        }
    }

    LOG_INFO("Update Neighbourhood Finished");
}

vector<Point<double>*> PSO::_particlesToPoints(vector<Particle*> _particles){
    vector<Point<double>*> points;

    for(unsigned int i = 0;i < _particles.size(); i++){
        points.push_back(&(_particles[i]->_position));
    }

    return points;
}

PSO::~PSO() {
    for (auto particle = _particles.begin(); particle != _particles.end(); ++particle) {
        delete (*particle);
    }
    _particles.clear();

    delete _wordsGenerator;
}



