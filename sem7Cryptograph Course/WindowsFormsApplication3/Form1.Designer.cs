namespace WindowsFormsApplication3
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.buttonEncode = new System.Windows.Forms.Button();
            this.buttonDecode = new System.Windows.Forms.Button();
            this.buttonExtendKey = new System.Windows.Forms.Button();
            this.buttonAddKey = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.listAddKey = new System.Windows.Forms.ListBox();
            this.label4 = new System.Windows.Forms.Label();
            this.progressFile = new System.Windows.Forms.ProgressBar();
            this.buttonSelect = new System.Windows.Forms.Button();
            this.listMode = new System.Windows.Forms.ListBox();
            this.label6 = new System.Windows.Forms.Label();
            this.labelFile = new System.Windows.Forms.Label();
            this.textBoxKey = new System.Windows.Forms.TextBox();
            this.textBoxInit = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(36, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Файл";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 32);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(33, 13);
            this.label2.TabIndex = 1;
            this.label2.Text = "Ключ";
            // 
            // buttonEncode
            // 
            this.buttonEncode.Location = new System.Drawing.Point(15, 61);
            this.buttonEncode.Name = "buttonEncode";
            this.buttonEncode.Size = new System.Drawing.Size(555, 23);
            this.buttonEncode.TabIndex = 2;
            this.buttonEncode.Text = "Кодировать";
            this.buttonEncode.UseVisualStyleBackColor = true;
            this.buttonEncode.Click += new System.EventHandler(this.buttonEncode_Click);
            // 
            // buttonDecode
            // 
            this.buttonDecode.Location = new System.Drawing.Point(15, 90);
            this.buttonDecode.Name = "buttonDecode";
            this.buttonDecode.Size = new System.Drawing.Size(555, 23);
            this.buttonDecode.TabIndex = 3;
            this.buttonDecode.Text = "Декодировать";
            this.buttonDecode.UseVisualStyleBackColor = true;
            this.buttonDecode.Click += new System.EventHandler(this.buttonDecode_Click);
            // 
            // buttonExtendKey
            // 
            this.buttonExtendKey.Location = new System.Drawing.Point(15, 119);
            this.buttonExtendKey.Name = "buttonExtendKey";
            this.buttonExtendKey.Size = new System.Drawing.Size(555, 23);
            this.buttonExtendKey.TabIndex = 4;
            this.buttonExtendKey.Text = "Расширить ключ";
            this.buttonExtendKey.UseVisualStyleBackColor = true;
            this.buttonExtendKey.Click += new System.EventHandler(this.buttonExtendKey_Click);
            // 
            // buttonAddKey
            // 
            this.buttonAddKey.Location = new System.Drawing.Point(15, 148);
            this.buttonAddKey.Name = "buttonAddKey";
            this.buttonAddKey.Size = new System.Drawing.Size(555, 23);
            this.buttonAddKey.TabIndex = 5;
            this.buttonAddKey.Text = "Сформировать дополнительный ключ";
            this.buttonAddKey.UseVisualStyleBackColor = true;
            this.buttonAddKey.Click += new System.EventHandler(this.buttonAddKey_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 183);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(123, 13);
            this.label3.TabIndex = 6;
            this.label3.Text = "Дополнительный ключ";
            // 
            // listAddKey
            // 
            this.listAddKey.FormattingEnabled = true;
            this.listAddKey.Items.AddRange(new object[] {
            "0",
            "0",
            "0",
            "0",
            "0",
            "0",
            "0",
            "0"});
            this.listAddKey.Location = new System.Drawing.Point(15, 199);
            this.listAddKey.Name = "listAddKey";
            this.listAddKey.Size = new System.Drawing.Size(120, 121);
            this.listAddKey.TabIndex = 7;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 338);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(70, 13);
            this.label4.TabIndex = 8;
            this.label4.Text = "Выполнение";
            // 
            // progressFile
            // 
            this.progressFile.Location = new System.Drawing.Point(88, 338);
            this.progressFile.Maximum = 1000;
            this.progressFile.Name = "progressFile";
            this.progressFile.Size = new System.Drawing.Size(482, 26);
            this.progressFile.Step = 1;
            this.progressFile.TabIndex = 9;
            // 
            // buttonSelect
            // 
            this.buttonSelect.Location = new System.Drawing.Point(156, 183);
            this.buttonSelect.Name = "buttonSelect";
            this.buttonSelect.Size = new System.Drawing.Size(414, 23);
            this.buttonSelect.TabIndex = 12;
            this.buttonSelect.Text = "Выбрать файл";
            this.buttonSelect.UseVisualStyleBackColor = true;
            this.buttonSelect.Click += new System.EventHandler(this.buttonSelect_Click);
            // 
            // listMode
            // 
            this.listMode.FormattingEnabled = true;
            this.listMode.Items.AddRange(new object[] {
            "(Электронная кодовая книга) ECB",
            "(Сцепление блоков) CBC",
            "(Обратная связь по шифротексту) CFB",
            "(Обратная связь по выходу) OFB"});
            this.listMode.Location = new System.Drawing.Point(156, 224);
            this.listMode.Name = "listMode";
            this.listMode.Size = new System.Drawing.Size(414, 95);
            this.listMode.TabIndex = 13;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(12, 385);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(87, 13);
            this.label6.TabIndex = 14;
            this.label6.Text = "Инициализация";
            // 
            // labelFile
            // 
            this.labelFile.AutoSize = true;
            this.labelFile.Location = new System.Drawing.Point(55, 8);
            this.labelFile.Name = "labelFile";
            this.labelFile.Size = new System.Drawing.Size(35, 13);
            this.labelFile.TabIndex = 15;
            this.labelFile.Text = "label7";
            // 
            // textBoxKey
            // 
            this.textBoxKey.Location = new System.Drawing.Point(58, 24);
            this.textBoxKey.Name = "textBoxKey";
            this.textBoxKey.Size = new System.Drawing.Size(512, 20);
            this.textBoxKey.TabIndex = 16;
            // 
            // textBoxInit
            // 
            this.textBoxInit.Location = new System.Drawing.Point(108, 382);
            this.textBoxInit.Name = "textBoxInit";
            this.textBoxInit.Size = new System.Drawing.Size(462, 20);
            this.textBoxInit.TabIndex = 17;
            this.textBoxInit.Text = "0";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(585, 414);
            this.Controls.Add(this.textBoxInit);
            this.Controls.Add(this.textBoxKey);
            this.Controls.Add(this.labelFile);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.listMode);
            this.Controls.Add(this.buttonSelect);
            this.Controls.Add(this.progressFile);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.listAddKey);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.buttonAddKey);
            this.Controls.Add(this.buttonExtendKey);
            this.Controls.Add(this.buttonDecode);
            this.Controls.Add(this.buttonEncode);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Name = "Form1";
            this.Text = "Курсовая. Алгоритм НРС";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button buttonEncode;
        private System.Windows.Forms.Button buttonDecode;
        private System.Windows.Forms.Button buttonExtendKey;
        private System.Windows.Forms.Button buttonAddKey;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ListBox listAddKey;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ProgressBar progressFile;
        private System.Windows.Forms.Button buttonSelect;
        private System.Windows.Forms.ListBox listMode;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label labelFile;
        private System.Windows.Forms.TextBox textBoxKey;
        private System.Windows.Forms.TextBox textBoxInit;
    }
}

