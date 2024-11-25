#ifndef HAPPY_H
#define HAPPY_H

#include "../CitizenState.h"

/**
 * @class Happy
 * @brief Represents the happy state of a Citizen.
 *
 * This class is a concrete implementation of the CitizenState interface,
 * indicating that a citizen is in a happy emotional state. It manages
 * transitions to other states based on changes in the citizen's situation.
 */
class Happy : public CitizenState
{
public:
    /**
     * @brief Handles a change in the citizen's situation, potentially transitioning
     *        to a different state.
     * @param change An integer representing the change that affects the citizen's state.
     * @return A pointer to the new CitizenState that results from the change.
     */
    CitizenState *handleChange(int change) override;

    /**
     * @brief Retrieves the name of the current state.
     * @return A string representing the name of the happy state.
     */
    std::string getState() override;

    /**
     * @brief Destructor for the Happy class.
     */
    ~Happy() {}
};

#endif // HAPPY_H
