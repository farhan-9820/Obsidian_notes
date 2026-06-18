smart contract must be **100% deterministic**. This means that given a specific input, it will _always_ produce the exact same output, no matter which computer on Earth runs the code, or when it is run.

- _Why?_ Because thousands of independent computers on a blockchain network must execute the code simultaneously and reach the exact same state. If a smart contract used a function like `GetRandomNumber()` or `GetCurrentWeather()`, different computers would get different results, and the network would break consensus.




