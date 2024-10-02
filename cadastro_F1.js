// Função para formatar e validar o CPF no formato XXX.XXX.XXX-XX
function formatarCPF(cpfInput) {
  let cpf = cpfInput.value.replace(/\D/g, ''); // Remove caracteres não numéricos

  if (cpf.length <= 11) {
    // Formatação do CPF
    cpf = cpf.replace(/(\d{3})(\d)/, "$1.$2");
    cpf = cpf.replace(/(\d{3})(\d)/, "$1.$2");
    cpf = cpf.replace(/(\d{3})(\d{1,2})$/, "$1-$2");
  }

  cpfInput.value = cpf;

  // Validação do CPF
  if (cpf.length === 14 && !validarCPF(cpf)) {
    alert("CPF inválido!");
    cpfInput.value = ''; // Limpa o campo se o CPF for inválido
  }
}

// Função para validar CPF
function validarCPF(cpf) {
  cpf = cpf.replace(/\D/g, ''); // Remove caracteres não numéricos
  if (cpf.length !== 11) return false;

  // Elimina CPFs com dígitos repetidos como 111.111.111-11
  if (/^(\d)\1{10}$/.test(cpf)) return false;

  let soma = 0, resto;

  // Validação do primeiro dígito verificador
  for (let i = 1; i <= 9; i++) soma += parseInt(cpf[i - 1]) * (11 - i);
  resto = (soma * 10) % 11;
  if (resto === 10 || resto === 11) resto = 0;
  if (resto !== parseInt(cpf[9])) return false;

  // Validação do segundo dígito verificador
  soma = 0;
  for (let i = 1; i <= 10; i++) soma += parseInt(cpf[i - 1]) * (12 - i);
  resto = (soma * 10) % 11;
  if (resto === 10 || resto === 11) resto = 0;
  if (resto !== parseInt(cpf[10])) return false;

  return true;
}

// Função para formatar o RG no formato XX.XXX.XXX-X
function formatarRG(rgInput) {
  let rg = rgInput.value.replace(/\D/g, ''); // Remove caracteres não numéricos

  if (rg.length <= 9) {
    rg = rg.replace(/(\d{2})(\d)/, "$1.$2");
    rg = rg.replace(/(\d{3})(\d)/, "$1.$2");
    rg = rg.replace(/(\d{3})(\d{1})$/, "$1-$2");
  }

  rgInput.value = rg;
}

// Função para formatar o Título de Eleitor no formato XXXX XXXX XXXX
function formatarTituloEleitor(tituloInput) {
  let titulo = tituloInput.value.replace(/\D/g, ''); // Remove caracteres não numéricos

  if (titulo.length <= 12) {
    titulo = titulo.replace(/(\d{4})(\d)/, "$1 $2");
    titulo = titulo.replace(/(\d{4})(\d)/, "$1 $2");
  }

  tituloInput.value = titulo;
}
// telefone
function formatarTelefone(telefoneInput) {
  let telefone = telefoneInput.value.replace(/\D/g, ''); // Remove caracteres não numéricos

  // Formatação do número após a remoção de caracteres não numéricos
  if (telefone.length === 11) { // Para números celulares (11 dígitos)
      telefone = telefone.replace(/(\d{2})(\d{5})(\d{4})/, "($1) $2-$3");
  } else if (telefone.length === 10) { // Para números fixos (10 dígitos)
      telefone = telefone.replace(/(\d{2})(\d{4})(\d{4})/, "($1) $2-$3");
  }

  telefoneInput.value = telefone;

  // Valida o número de telefone apenas se já houver 10 ou 11 dígitos
  const telefoneNumeros = telefone.replace(/\D/g, ''); // Remove formatação para validação
  if (telefoneNumeros.length === 10 || telefoneNumeros.length === 11) {
      if (!validarTelefone(telefoneNumeros)) {
          alert("Número Inválido");
          telefoneInput.value = ''; // Limpa o campo telefone
      }
  }
}

function validarTelefone(telefone) {
  // Regex para validar números de telefone com 10 ou 11 dígitos
  const phoneRegex = /^(?!0)[1-9]{2}(9[0-9]{4}[0-9]{4}|[0-9]{4}[0-9]{4})$/;

  // Verifica se o telefone corresponde à regex (somente dígitos)
  return phoneRegex.test(telefone);
}


// Função para formatar o CEP no formato XXXXX-XXX
function formatarCEP(cepInput) {
  let cep = cepInput.value.replace(/\D/g, ''); // Remove caracteres não numéricos

  if (cep.length > 5) {
    cep = cep.replace(/(\d{5})(\d{3})/, "$1-$2");
  }

  cepInput.value = cep;
}

// Função para formatar o PIS/NIS/PASEP no formato XXXXXXXXXXX
function formatarPisNisPasep(pisInput) {
  let pis = pisInput.value.replace(/\D/g, ''); // Remove caracteres não numéricos

  if (pis.length > 11) {
    pis = pis.substring(0, 11); // Restringe o valor a 11 caracteres
  }

  pisInput.value = pis;
}

// Limpar os inputs ao carregar a página
window.addEventListener('DOMContentLoaded', () => {
  const inputs = document.querySelectorAll('input, textarea');
  inputs.forEach(input => {
    input.value = ''; // Limpa os valores dos inputs
  });
});

// Perguntar ao usuário se ele realmente deseja sair da página
window.addEventListener('beforeunload', (event) => {
  // Exibe a mensagem de saída. A maioria dos navegadores ignora mensagens personalizadas, mas o comportamento padrão ainda pergunta ao usuário.
  event.preventDefault(); // Método recomendado para garantir o funcionamento
  event.returnValue = ''; // Definir uma string vazia para acionar a mensagem padrão do navegador(usado em alguns navegadores)
});
