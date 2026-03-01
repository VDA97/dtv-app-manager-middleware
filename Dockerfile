# ESTÁGIO 1: Compilação
FROM ubuntu:22.04 AS builder
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential cmake git libgtest-dev nlohmann-json3-dev libspdlog-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

# Aqui compilamos TUDO (o App e os Testes)
RUN mkdir build && cd build && \
    cmake .. && \
    make -j$(nproc)

# --- ESTÁGIO 2: Validação (A "Barreira" de Qualidade) ---
# O Docker vai tentar rodar os testes agora. 
# Se algum teste falhar, o build trava aqui e não cria a imagem final!
RUN ./build/app_manager_test

# --- ESTÁGIO 3: Imagem Final ---
# --- ESTÁGIO 3: Imagem Final de Produção ---
FROM ubuntu:22.04
WORKDIR /runtime

ENV DEBIAN_FRONTEND=noninteractive

# Instalamos as bibliotecas de runtime (spdlog e GTest)
# Nota: Adicionei libgtest-dev aqui se seus testes precisarem de algo dinâmico
RUN apt-get update && apt-get install -y \
    libspdlog1 \
    libgtest-dev \ 
    && rm -rf /var/lib/apt/lists/*

# COPIE OS DOIS BINÁRIOS AQUI!
COPY --from=builder /app/build/dtv_middleware .
COPY --from=builder /app/build/app_manager_test .

# Deixe o Middleware como padrão
CMD ["./dtv_middleware"]