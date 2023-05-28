# Spécification du Composant HMACSHA512 en C++ et Python

## Auteurs
Mehdi EL AYADI, Yufei Liu, Qilian Gu

## Historique des versions
| Version | Date       | Description                 |
|---------|------------|-----------------------------|
| 1.0     | 26/05/2023 | Première version du document|

## Description

### Contexte
Le composant HMACSHA512 est un module de cryptographie qui fournit une fonction de hachage cryptographique pour la sécurité des données. Il est basé sur l'algorithme HMAC (Hash-based Message Authentication Code) et utilise SHA512 comme fonction de hachage sous-jacente.

### Schéma bloc incluant les composants connexes
```
[Application] --> [HMACSHA512 Composant] --> [SHA512]
```
L'application interagit avec le composant HMACSHA512, qui à son tour utilise le composant SHA512.

### Interface et interaction avec chaque autre composant
L'interface du composant HMACSHA512 est conçue pour être simple et directe. Elle fournit une fonction `hmac_sha512(key, message)` qui prend une clé et un message en entrée, et renvoie le hachage HMACSHA512 du message.

### Résumé: déclarations de fonctions python d’interface et leurs arguments
```python
def hmac_sha512(key: bytes, message: bytes) -> bytes:
    """
    Calcule le HMACSHA512 du message avec la clé donnée.

    Args:
        key (bytes): La clé utilisée pour le hachage.
        message (bytes): Le message à hacher.

    Returns:
        bytes: Le hachage HMACSHA512 du message.
    """
```

### Cas d’erreurs
Si la clé ou le message ne sont pas de type `bytes`, une `TypeError` sera levée. Si la clé est vide, une `ValueError` sera levée.

## Test

### Plan de test
Nous testerons la fonction `hmac_sha512` avec différentes clés et messages, y compris des cas limites comme une clé vide ou un message vide. Nous vérifierons que la fonction renvoie le bon hachage et qu'elle lève les exceptions appropriées en cas d'erreur.

### Programme de test
```python
def test_hmac_sha512():
    # Test avec des valeurs valides
    key = b"secret"
    message = b"Hello, World!"
    assert hmac_sha512(key, message) == b'\x9b\x61\x...'

    # Test avec une clé vide
    try:
        hmac_sha512(b'', message)
    except ValueError:
        pass
    else:
        assert False, "Expected ValueError for empty key"

    # Test avec un type de clé invalide
    try:
        hmac_sha512("not bytes", message)
    except TypeError:
        pass
    else:
        assert False, "Expected TypeError for key of wrong type"

    # Test avec un type de message invalide
    try:
        hmac_sha512(key, "not bytes")
    except TypeError:
        pass
    else:
        assert False, "Expected TypeError for message of wrong type"
```
Pour exécuter les tests, utilisez simplement la commande `python -m test test_hmac_sha512`.
