''' Sergey Cherepanov st129987@student.spbu.ru
   Assignment1
'''

import subprocess
import base64
import pytest
import random
import string

def run_encoder(input_data: str) -> str:
    process = subprocess.run(
        ['./ascii85', '-e'],
        input=input_data.encode('utf-8'),
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE
    )
    if process.returncode != 0:
        pytest.fail(f"Encoder failed with error: {process.stderr.decode()}")
    return process.stdout.decode('utf-8').strip()

def run_decoder(input_data: str) -> subprocess.CompletedProcess:
    return subprocess.run(
        ['./ascii85', '-d'],
        input=input_data.encode('utf-8'),
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE
    )

def random_ascii_string(length=10):
    return ''.join(random.choices(string.ascii_letters + string.digits, k=length))

@pytest.mark.parametrize('_', range(5))
def test_encoder_random_input(_):
    data = random_ascii_string(random.randint(1, 20))
    assert run_encoder(data) == base64.a85encode(data.encode()).decode()

@pytest.mark.parametrize('_', range(5))
def test_decoder_random_valid(_):
    data = random_ascii_string(random.randint(1, 20))
    encoded = base64.a85encode(data.encode()).decode()
    result = run_decoder(encoded)
    assert result.returncode == 0
    assert result.stdout.decode().strip() == data

@pytest.mark.parametrize("invalid_input", [
    "7",
    "87cUR!",
    "invalid\x00",
])
def test_decoder_invalid_data(invalid_input):
    result = run_decoder(invalid_input)
    assert result.returncode != 0
