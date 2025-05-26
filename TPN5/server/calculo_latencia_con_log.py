import re
from datetime import datetime

def leer_latencias(nombre_archivo):
    latencias = []
    patron = re.compile(r'\[(.*?)\]\s+(Sent|Received):')
    with open(nombre_archivo, 'r') as f:
        lines = f.readlines()
        for i in range(len(lines) - 1):
            sent_match = patron.match(lines[i])
            recv_match = patron.match(lines[i+1])
            if sent_match and sent_match.group(2) == "Sent" and recv_match and recv_match.group(2) == "Received":
                t1 = datetime.strptime(sent_match.group(1), "%Y-%m-%d %H:%M:%S")
                t2 = datetime.strptime(recv_match.group(1), "%Y-%m-%d %H:%M:%S")
                latencia = (t2 - t1).total_seconds() * 1000  # en ms
                latencias.append(latencia)
    return latencias

def calcular_estadisticas(latencias):
    promedio = sum(latencias) / len(latencias)
    maxima = max(latencias)
    minima = min(latencias)
    jitter = sum(abs(latencias[i] - latencias[i-1]) for i in range(1, len(latencias))) / (len(latencias) - 1)
    return promedio, maxima, minima, jitter

if __name__ == "__main__":
    # archivo = "server.log" USADA PARA EL LOG DE TCP
    archivo = "server_udp.log"
    latencias = leer_latencias(archivo)
    if not latencias:
        print("No se encontraron pares Sent/Received en el archivo.")
    else:
        promedio, maxima, minima, jitter = calcular_estadisticas(latencias)
        print(f"Latencia promedio: {promedio:.3f} ms")
        print(f"Latencia máxima: {maxima:.3f} ms")
        print(f"Latencia mínima: {minima:.3f} ms")
        print(f"Jitter: {jitter:.3f} ms")