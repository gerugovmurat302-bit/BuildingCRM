#pragma once

#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
namespace BuildingCRM {

    // Форма регистраций
    public ref class RegisterForm : public Form {
    private:
        TextBox^ txtFIO;
        TextBox^ txtLogin;
        TextBox^ txtPassword;
        TextBox^ txtPasswordRepeat;
        ComboBox^ cmbRole;

    public:
        RegisterForm() {
            this->Text = L"Регистрация";
            this->Size = System::Drawing::Size(450, 380);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->MaximizeBox = false;

            // ФИО
            Label^ lblFIO = gcnew Label();
            lblFIO->Text = L"Фамилия Имя Отчество:";
            lblFIO->Location = System::Drawing::Point(30, 30);
            lblFIO->Size = System::Drawing::Size(150, 25);
            this->Controls->Add(lblFIO);

            txtFIO = gcnew TextBox();
            txtFIO->Location = System::Drawing::Point(190, 30);
            txtFIO->Size = System::Drawing::Size(200, 25);
            this->Controls->Add(txtFIO);

            // Логин / Email
            Label^ lblLogin = gcnew Label();
            lblLogin->Text = L"Логин / Email:";
            lblLogin->Location = System::Drawing::Point(30, 70);
            lblLogin->Size = System::Drawing::Size(150, 25);
            this->Controls->Add(lblLogin);

            txtLogin = gcnew TextBox();
            txtLogin->Location = System::Drawing::Point(190, 70);
            txtLogin->Size = System::Drawing::Size(200, 25);
            this->Controls->Add(txtLogin);

            // Пароль
            Label^ lblPassword = gcnew Label();
            lblPassword->Text = L"Пароль:";
            lblPassword->Location = System::Drawing::Point(30, 110);
            lblPassword->Size = System::Drawing::Size(150, 25);
            this->Controls->Add(lblPassword);

            txtPassword = gcnew TextBox();
            txtPassword->Location = System::Drawing::Point(190, 110);
            txtPassword->Size = System::Drawing::Size(200, 25);
            txtPassword->PasswordChar = '*';
            this->Controls->Add(txtPassword);

            // Повторить пароль
            Label^ lblPasswordRepeat = gcnew Label();
            lblPasswordRepeat->Text = L"Повторить пароль:";
            lblPasswordRepeat->Location = System::Drawing::Point(30, 150);
            lblPasswordRepeat->Size = System::Drawing::Size(150, 25);
            this->Controls->Add(lblPasswordRepeat);

            txtPasswordRepeat = gcnew TextBox();
            txtPasswordRepeat->Location = System::Drawing::Point(190, 150);
            txtPasswordRepeat->Size = System::Drawing::Size(200, 25);
            txtPasswordRepeat->PasswordChar = '*';
            this->Controls->Add(txtPasswordRepeat);

            // Роль
            Label^ lblRole = gcnew Label();
            lblRole->Text = L"Роль:";
            lblRole->Location = System::Drawing::Point(30, 190);
            lblRole->Size = System::Drawing::Size(150, 25);
            this->Controls->Add(lblRole);

            cmbRole = gcnew ComboBox();
            cmbRole->Location = System::Drawing::Point(190, 190);
            cmbRole->Size = System::Drawing::Size(200, 25);
            cmbRole->Items->Add(L"Менеджер");
            cmbRole->Items->Add(L"Исполнитель");
            cmbRole->Items->Add(L"Бухгалтер");
            cmbRole->SelectedIndex = 0;
            this->Controls->Add(cmbRole);

            // Кнопка создания аккаунта
            Button^ btnCreate = gcnew Button();
            btnCreate->Text = L"Создать аккаунт";
            btnCreate->Location = System::Drawing::Point(150, 240);
            btnCreate->Size = System::Drawing::Size(150, 35);
            btnCreate->Click += gcnew EventHandler(this, &RegisterForm::OnRegisterClick);
            this->Controls->Add(btnCreate);
        }

    private:
        void OnRegisterClick(Object^ sender, EventArgs^ e) {
            if (txtPassword->Text != txtPasswordRepeat->Text) {
                MessageBox::Show(L"Пароли не совпадают!", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }
            MessageBox::Show(
                L"Регистрация выполнена!\nФИО: " + txtFIO->Text +
                L"\nЛогин: " + txtLogin->Text +
                L"\nРоль: " + cmbRole->SelectedItem->ToString(),
                L"Успех", MessageBoxButtons::OK, MessageBoxIcon::Information
            );
            this->Close();
        }
    };

    // Страница менеджера
    public ref class ManagerForm : public Form {
    public:
        ManagerForm() {
            this->Text = L"Страница менеджера";
            this->Size = System::Drawing::Size(850, 550);
            this->StartPosition = FormStartPosition::CenterScreen;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;

            // Заголовок "Задачи"
            Label^ lblTitle = gcnew Label();
            lblTitle->Text = L"Задачи";
            lblTitle->Font = gcnew System::Drawing::Font(L"Segoe UI", 16, FontStyle::Bold);
            lblTitle->Location = System::Drawing::Point((this->ClientSize.Width - 80) / 2, 20);
            lblTitle->AutoSize = true;
            this->Controls->Add(lblTitle);

            // Таблица задач ( ListView )
            ListView^ lvTasks = gcnew ListView();
            lvTasks->Location = System::Drawing::Point(30, 70);
            lvTasks->Size = System::Drawing::Size(770, 300);
            lvTasks->View = View::Details;
            lvTasks->FullRowSelect = true;
            lvTasks->GridLines = true;

            // Колонки
            lvTasks->Columns->Add(L"Название задачи", 280);
            lvTasks->Columns->Add(L"Статус", 130);
            lvTasks->Columns->Add(L"Срок", 130);
            lvTasks->Columns->Add(L"Исполнитель", 150);

            // Пример данных
            ListViewItem^ item1 = gcnew ListViewItem(L"Разработать ТЗ");
            item1->SubItems->Add(L"В работе");
            item1->SubItems->Add(L"10.05.2026");
            item1->SubItems->Add(L"Иванов И.И.");
            lvTasks->Items->Add(item1);

            ListViewItem^ item2 = gcnew ListViewItem(L"Спроектировать БД");
            item2->SubItems->Add(L"Завершена");
            item2->SubItems->Add(L"20.04.2026");
            item2->SubItems->Add(L"Петров П.П.");
            lvTasks->Items->Add(item2);

            ListViewItem^ item3 = gcnew ListViewItem(L"Настроить сервер");
            item3->SubItems->Add(L"В ожидании");
            item3->SubItems->Add(L"15.06.2026");
            item3->SubItems->Add(L"Сидоров С.С.");
            lvTasks->Items->Add(item3);

            this->Controls->Add(lvTasks);

            // панель для кнопок
            TableLayoutPanel^ buttonPanel = gcnew TableLayoutPanel();
            buttonPanel->Location = System::Drawing::Point(50, 400);
            buttonPanel->Size = System::Drawing::Size(730, 50);
            buttonPanel->ColumnCount = 3;
            buttonPanel->RowCount = 1;
            buttonPanel->ColumnStyles->Add(gcnew ColumnStyle(SizeType::Percent, 33.33f));
            buttonPanel->ColumnStyles->Add(gcnew ColumnStyle(SizeType::Percent, 33.33f));
            buttonPanel->ColumnStyles->Add(gcnew ColumnStyle(SizeType::Percent, 33.33f));

            // Кнопка 1
            Button^ btnAssign = gcnew Button();
            btnAssign->Text = L"Назначить задачу";
            btnAssign->Dock = DockStyle::Fill;
            btnAssign->Size = System::Drawing::Size(200, 40);

            // Кнопка 2
            Button^ btnUsers = gcnew Button();
            btnUsers->Text = L"Пользователи";
            btnUsers->Dock = DockStyle::Fill;
            btnUsers->Size = System::Drawing::Size(200, 40);

            // Кнопка 3
            Button^ btnReports = gcnew Button();
            btnReports->Text = L"Отчеты";
            btnReports->Dock = DockStyle::Fill;
            btnReports->Size = System::Drawing::Size(200, 40);

            buttonPanel->Controls->Add(btnAssign, 0, 0);
            buttonPanel->Controls->Add(btnUsers, 1, 0);
            buttonPanel->Controls->Add(btnReports, 2, 0);

            this->Controls->Add(buttonPanel);
        }
    };

    public ref class ExecutorForm : public Form {
    private:
        TextBox^ txtTaskName;
        TextBox^ txtStatus;
        TextBox^ txtDeadline;
        Button^ btnFile;
        Button^ btnReport;
        Button^ btnSend;
        Label^ lblFileStatus;

        // Страница исполнителя
    public:
        ExecutorForm() {
            this->Text = L"Мои задачи";
            this->Size = System::Drawing::Size(500, 400);
            this->StartPosition = FormStartPosition::CenterScreen;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;

            int labelX = 30;
            int fieldX = 180;
            int fieldWidth = 240;
            int y = 30;
            int step = 50;

            // Название задачи
            Label^ lblTask = gcnew Label();
            lblTask->Text = L"Название задачи:";
            lblTask->Location = System::Drawing::Point(labelX, y);
            lblTask->Size = System::Drawing::Size(130, 25);
            this->Controls->Add(lblTask);

            txtTaskName = gcnew TextBox();
            txtTaskName->Location = System::Drawing::Point(fieldX, y);
            txtTaskName->Size = System::Drawing::Size(fieldWidth, 25);
            this->Controls->Add(txtTaskName);
            y += step;

            // Статус
            Label^ lblStatus = gcnew Label();
            lblStatus->Text = L"Статус:";
            lblStatus->Location = System::Drawing::Point(labelX, y);
            lblStatus->Size = System::Drawing::Size(130, 25);
            this->Controls->Add(lblStatus);

            txtStatus = gcnew TextBox();
            txtStatus->Location = System::Drawing::Point(fieldX, y);
            txtStatus->Size = System::Drawing::Size(fieldWidth, 25);
            this->Controls->Add(txtStatus);
            y += step;

            // Срок
            Label^ lblDeadline = gcnew Label();
            lblDeadline->Text = L"Срок:";
            lblDeadline->Location = System::Drawing::Point(labelX, y);
            lblDeadline->Size = System::Drawing::Size(130, 25);
            this->Controls->Add(lblDeadline);

            txtDeadline = gcnew TextBox();
            txtDeadline->Location = System::Drawing::Point(fieldX, y);
            txtDeadline->Size = System::Drawing::Size(fieldWidth, 25);
            txtDeadline->Text = L"ДД.ММ.ГГГГ";
            this->Controls->Add(txtDeadline);
            y += step;

            // Прикрепить файл
            Label^ lblFile = gcnew Label();
            lblFile->Text = L"Прикрепить файл:";
            lblFile->Location = System::Drawing::Point(labelX, y);
            lblFile->Size = System::Drawing::Size(120, 25);
            this->Controls->Add(lblFile);

            btnFile = gcnew Button();
            btnFile->Text = L"Выбрать файл";
            btnFile->Location = System::Drawing::Point(fieldX, y);
            btnFile->Size = System::Drawing::Size(120, 30);
            btnFile->Click += gcnew EventHandler(this, &ExecutorForm::OnFileClick);
            this->Controls->Add(btnFile);

            lblFileStatus = gcnew Label();
            lblFileStatus->Text = L"Файл не выбран";
            lblFileStatus->Location = System::Drawing::Point(fieldX + 130, y + 5);
            lblFileStatus->Size = System::Drawing::Size(150, 25);
            this->Controls->Add(lblFileStatus);
            y += step + 10;

            // Кнопки Отчитаться и Отправить
            btnReport = gcnew Button();
            btnReport->Text = L"Отчитаться";
            btnReport->Location = System::Drawing::Point(labelX, y);
            btnReport->Size = System::Drawing::Size(180, 40);
            btnReport->Click += gcnew EventHandler(this, &ExecutorForm::OnReportClick);
            this->Controls->Add(btnReport);

            btnSend = gcnew Button();
            btnSend->Text = L"Отправить";
            btnSend->Location = System::Drawing::Point(labelX + 200, y);
            btnSend->Size = System::Drawing::Size(180, 40);
            btnSend->Click += gcnew EventHandler(this, &ExecutorForm::OnSendClick);
            this->Controls->Add(btnSend);
        }

    private:
        void OnFileClick(Object^ sender, EventArgs^ e) {
            lblFileStatus->Text = L"Файл выбран";
        }

        void OnReportClick(Object^ sender, EventArgs^ e) {
            String^ msg = L"Отчёт по задаче\n";
            msg += L"Задача: " + txtTaskName->Text + L"\n";
            msg += L"Статус: " + txtStatus->Text + L"\n";
            msg += L"Срок: " + txtDeadline->Text + L"\n";
            msg += L"Файл: " + lblFileStatus->Text;
            MessageBox::Show(msg, L"Отчёт");
        }

        void OnSendClick(Object^ sender, EventArgs^ e) {
            MessageBox::Show(L"Отправлено руководителю", L"Отправка");
        }
    };

    // Страница бухгалтера

   public ref class AccountantForm : public Form {
private:
    TextBox^ txtProject;
    TextBox^ txtBudget;
    TextBox^ txtExpenses;
    TextBox^ txtRemain;
    Button^ btnReport;

public:
    AccountantForm() {
        this->Text = L"Бюджет проектов";
        this->Size = System::Drawing::Size(450, 350);
        this->StartPosition = FormStartPosition::CenterScreen;
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
        this->MaximizeBox = false;

        int labelX = 20;
        int fieldX = 180;
        int fieldWidth = 200;
        int y = 30;
        int step = 50;

        // Название проекта
        Label^ lblProject = gcnew Label();
        lblProject->Text = L"Название проекта:";
        lblProject->Location = System::Drawing::Point(labelX, y);
        lblProject->Size = System::Drawing::Size(150, 25);
        this->Controls->Add(lblProject);

        txtProject = gcnew TextBox();
        txtProject->Location = System::Drawing::Point(fieldX, y);
        txtProject->Size = System::Drawing::Size(fieldWidth, 25);
        this->Controls->Add(txtProject);
        y += step;

        // Бюджет проекта
        Label^ lblBudget = gcnew Label();
        lblBudget->Text = L"Бюджет проекта:";
        lblBudget->Location = System::Drawing::Point(labelX, y);
        lblBudget->Size = System::Drawing::Size(150, 25);
        this->Controls->Add(lblBudget);

        txtBudget = gcnew TextBox();
        txtBudget->Location = System::Drawing::Point(fieldX, y);
        txtBudget->Size = System::Drawing::Size(fieldWidth, 25);
        this->Controls->Add(txtBudget);
        y += step;

        // Расходы
        Label^ lblExpenses = gcnew Label();
        lblExpenses->Text = L"Расходы:";
        lblExpenses->Location = System::Drawing::Point(labelX, y);
        lblExpenses->Size = System::Drawing::Size(150, 25);
        this->Controls->Add(lblExpenses);

        txtExpenses = gcnew TextBox();
        txtExpenses->Location = System::Drawing::Point(fieldX, y);
        txtExpenses->Size = System::Drawing::Size(fieldWidth, 25);
        this->Controls->Add(txtExpenses);
        y += step;

        // Остаток
        Label^ lblRemain = gcnew Label();
        lblRemain->Text = L"Остаток:";
        lblRemain->Location = System::Drawing::Point(labelX, y);
        lblRemain->Size = System::Drawing::Size(150, 25);
        this->Controls->Add(lblRemain);

        txtRemain = gcnew TextBox();
        txtRemain->Location = System::Drawing::Point(fieldX, y);
        txtRemain->Size = System::Drawing::Size(fieldWidth, 25);
        txtRemain->ReadOnly = true;
        txtRemain->BackColor = System::Drawing::Color::LightGray;
        this->Controls->Add(txtRemain);
        y += step + 10;

        // Кнопка отчёта
        btnReport = gcnew Button();
        btnReport->Text = L"Сформировать финансовый отчет";
        btnReport->Location = System::Drawing::Point(20, y);
        btnReport->Size = System::Drawing::Size(390, 40);
        btnReport->Click += gcnew EventHandler(this, &AccountantForm::OnReportClick);
        this->Controls->Add(btnReport);
    }

private:
    void UpdateRemain() {
        try {
            double budget = Double::Parse(txtBudget->Text);
            double expenses = Double::Parse(txtExpenses->Text);
            double remain = budget - expenses;
            txtRemain->Text = remain.ToString();
        }
        catch (...) {
            txtRemain->Text = L"Ошибка ввода";
        }
    }

    void OnReportClick(Object^ sender, EventArgs^ e) {
        UpdateRemain();
        String^ report = L"Финансовый отчет\n";
        report += L"Проект: " + txtProject->Text + L"\n";
        report += L"Бюджет: " + txtBudget->Text + L"\n";
        report += L"Расходы: " + txtExpenses->Text + L"\n";
        report += L"Остаток: " + txtRemain->Text;
        MessageBox::Show(report, L"Отчет");
    }
};

// Форма авторизаций
public ref class MainForm : public Form {
private:
    TextBox^ txtLogin;
    TextBox^ txtPassword;
    ComboBox^ cmbRole;

public:
    MainForm() {
        InitializeComponent();
    }

private:
    void InitializeComponent() {
        this->Text = L"Авторизация пользователя";
        this->Size = System::Drawing::Size(450, 330);
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
        this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;

        // Логин / Email
        Label^ lblLogin = gcnew Label();
        lblLogin->Text = L"Логин / Email:";
        lblLogin->Location = System::Drawing::Point(40, 40);
        lblLogin->Size = System::Drawing::Size(120, 25);
        this->Controls->Add(lblLogin);

        txtLogin = gcnew TextBox();
        txtLogin->Location = System::Drawing::Point(170, 40);
        txtLogin->Size = System::Drawing::Size(200, 25);
        this->Controls->Add(txtLogin);

        // Пароль
        Label^ lblPassword = gcnew Label();
        lblPassword->Text = L"Пароль:";
        lblPassword->Location = System::Drawing::Point(40, 80);
        lblPassword->Size = System::Drawing::Size(120, 25);
        this->Controls->Add(lblPassword);

        txtPassword = gcnew TextBox();
        txtPassword->Location = System::Drawing::Point(170, 80);
        txtPassword->Size = System::Drawing::Size(200, 25);
        txtPassword->PasswordChar = '*';
        this->Controls->Add(txtPassword);

        // Роль
        Label^ lblRole = gcnew Label();
        lblRole->Text = L"Роль:";
        lblRole->Location = System::Drawing::Point(40, 120);
        lblRole->Size = System::Drawing::Size(120, 25);
        this->Controls->Add(lblRole);

        cmbRole = gcnew ComboBox();
        cmbRole->Location = System::Drawing::Point(170, 120);
        cmbRole->Size = System::Drawing::Size(200, 25);
        cmbRole->Items->Add(L"Менеджер");
        cmbRole->Items->Add(L"Исполнитель");
        cmbRole->Items->Add(L"Бухгалтер");
        cmbRole->SelectedIndex = 0;
        this->Controls->Add(cmbRole);

        // Кнопка Войти
        Button^ btnLogin = gcnew Button();
        btnLogin->Text = L"Войти";
        btnLogin->Location = System::Drawing::Point(170, 170);
        btnLogin->Size = System::Drawing::Size(100, 35);
        btnLogin->Click += gcnew EventHandler(this, &MainForm::OnLoginClick);
        this->Controls->Add(btnLogin);

        // Кнопка Зарегистрироваться
        Button^ btnRegister = gcnew Button();
        btnRegister->Text = L"Зарегистрироваться";
        btnRegister->Location = System::Drawing::Point(280, 170);
        btnRegister->Size = System::Drawing::Size(130, 35);
        btnRegister->Click += gcnew EventHandler(this, &MainForm::OnRegisterClick);
        this->Controls->Add(btnRegister);
    }

    void OnLoginClick(Object^ sender, EventArgs^ e) {
        String^ role = cmbRole->SelectedItem->ToString();

        if (role == L"Менеджер") {
            ManagerForm^ form = gcnew ManagerForm();
            form->Show();
            this->Hide();
        }
        else if (role == L"Исполнитель") {
            ExecutorForm^ form = gcnew ExecutorForm();
            form->Show();
            this->Hide();
        }
        else if (role == L"Бухгалтер") {
            AccountantForm^ form = gcnew AccountantForm();
            form->Show();
            this->Hide();
        }
        else {
            MessageBox::Show(L"Неизвестная роль", L"Ошибка");
        }
    }

    void OnRegisterClick(Object^ sender, EventArgs^ e) {
        RegisterForm^ form = gcnew RegisterForm();
        form->ShowDialog();
    }
};
}