import pickle

def save_to_pickle(dictionary: dict, path: str):

    # Save the dictionary to a file
    with open(f"{path}.pkl", "wb") as f:
        pickle.dump(dictionary, f)

def read_from_pickle(path: str):

    # Read the dictionary from pickle
    with open(f"{path}.pkl", "rb") as f:
        dictionary = pickle.load(f)

    return dictionary