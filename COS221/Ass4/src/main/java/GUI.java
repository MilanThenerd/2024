import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.sql.*;
import java.util.ArrayList;
import java.util.Properties;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JFrame;
import javax.swing.table.DefaultTableModel;

public class GUI extends javax.swing.JFrame 
{
    private String protocol;
    private String host;
    private int port;
    private String dbName;
    private String username;
    private String password;

    public GUI() throws ClassNotFoundException, SQLException, FileNotFoundException, IOException 
    {
        initComponents();

        Properties prop = new Properties();
        FileInputStream input = new FileInputStream("configuration.properties");
        prop.load(input);

        protocol = prop.getProperty("dvdrental.DB.PROTO");
        host = prop.getProperty("dvdrental.DB.HOST");
        port = Integer.parseInt(prop.getProperty("dvdrental.DB.PORT"));
        dbName = prop.getProperty("dvdrental.DB.NAME");
        username = prop.getProperty("dvdrental.DB.USERNAME");
        password = prop.getProperty("dvdrental.DB.PASSWORD");

        input.close();

        populateStaffTable();
        populateReportTable();
        populateFilmsTable();
        populateCustomerTable();
    }
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jPanel1 = new javax.swing.JPanel();
        jTabbedPane1 = new javax.swing.JTabbedPane();
        Staff = new javax.swing.JPanel();
        jPanel3 = new javax.swing.JPanel();
        jScrollPane1 = new javax.swing.JScrollPane();
        StaffTable = new javax.swing.JTable();
        chkFirstName = new javax.swing.JCheckBox();
        chkLastName = new javax.swing.JCheckBox();
        chkAddress = new javax.swing.JCheckBox();
        chkDistrict = new javax.swing.JCheckBox();
        chkCity = new javax.swing.JCheckBox();
        chkPostal = new javax.swing.JCheckBox();
        chkPhone = new javax.swing.JCheckBox();
        chkStore = new javax.swing.JCheckBox();
        chkActive = new javax.swing.JCheckBox();
        Film = new javax.swing.JPanel();
        jPanel4 = new javax.swing.JPanel();
        AddFilmsBtn = new javax.swing.JToggleButton();
        jScrollPane3 = new javax.swing.JScrollPane();
        FilmsTable = new javax.swing.JTable();
        SearchFieldFilms = new javax.swing.JTextField();
        SearchFilmsBtn = new javax.swing.JButton();
        Report = new javax.swing.JPanel();
        jScrollPane2 = new javax.swing.JScrollPane();
        ReportTable = new javax.swing.JTable();
        Notifications = new javax.swing.JPanel();
        jButton1 = new javax.swing.JButton();
        jScrollPane4 = new javax.swing.JScrollPane();
        CustomerTable = new javax.swing.JTable();
        SearchCustomerField = new javax.swing.JTextField();
        SearchCustomersBtn = new javax.swing.JButton();
        DroppedSubChk = new javax.swing.JCheckBox();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

        jPanel1.setBackground(new java.awt.Color(0, 153, 153));

        jTabbedPane1.setBackground(new java.awt.Color(0, 153, 153));
        jTabbedPane1.setFont(new java.awt.Font("Segoe UI", 0, 36)); // NOI18N

        jPanel3.setBackground(new java.awt.Color(204, 255, 255));

        StaffTable.setModel(new javax.swing.table.DefaultTableModel(
            new Object [][] {

            },
            new String [] {

            }
        ));
        jScrollPane1.setViewportView(StaffTable);

        chkFirstName.setText("FirstName");
        chkFirstName.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                chkFirstNameActionPerformed(evt);
            }
        });

        chkLastName.setText("LastName");
        chkLastName.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                chkLastNameActionPerformed(evt);
            }
        });

        chkAddress.setText("Address");
        chkAddress.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                chkAddressActionPerformed(evt);
            }
        });

        chkDistrict.setText("District");
        chkDistrict.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                chkDistrictActionPerformed(evt);
            }
        });

        chkCity.setText("City");
        chkCity.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                chkCityActionPerformed(evt);
            }
        });

        chkPostal.setText("Postal Code");
        chkPostal.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                chkPostalActionPerformed(evt);
            }
        });

        chkPhone.setText("Phone");
        chkPhone.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                chkPhoneActionPerformed(evt);
            }
        });

        chkStore.setText("Store");
        chkStore.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                chkStoreActionPerformed(evt);
            }
        });

        chkActive.setText("Active Status");
        chkActive.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                chkActiveActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout jPanel3Layout = new javax.swing.GroupLayout(jPanel3);
        jPanel3.setLayout(jPanel3Layout);
        jPanel3Layout.setHorizontalGroup(
            jPanel3Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel3Layout.createSequentialGroup()
                .addGap(17, 17, 17)
                .addGroup(jPanel3Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addComponent(jScrollPane1)
                    .addGroup(jPanel3Layout.createSequentialGroup()
                        .addComponent(chkFirstName)
                        .addGap(18, 18, 18)
                        .addComponent(chkLastName)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(chkAddress)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(chkDistrict)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(chkCity)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(chkPostal)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(chkPhone)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(chkStore)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(chkActive)))
                .addContainerGap(43, Short.MAX_VALUE))
        );
        jPanel3Layout.setVerticalGroup(
            jPanel3Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel3Layout.createSequentialGroup()
                .addGap(112, 112, 112)
                .addGroup(jPanel3Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(chkFirstName)
                    .addComponent(chkLastName)
                    .addComponent(chkAddress)
                    .addComponent(chkDistrict)
                    .addComponent(chkCity)
                    .addComponent(chkPostal)
                    .addComponent(chkPhone)
                    .addComponent(chkStore)
                    .addComponent(chkActive))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 295, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(31, 31, 31))
        );

        javax.swing.GroupLayout StaffLayout = new javax.swing.GroupLayout(Staff);
        Staff.setLayout(StaffLayout);
        StaffLayout.setHorizontalGroup(
            StaffLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jPanel3, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );
        StaffLayout.setVerticalGroup(
            StaffLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jPanel3, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );

        jTabbedPane1.addTab("Staff", Staff);

        jPanel4.setBackground(new java.awt.Color(204, 255, 255));

        AddFilmsBtn.setText("Add");
        AddFilmsBtn.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                AddFilmsBtnActionPerformed(evt);
            }
        });

        FilmsTable.setModel(new javax.swing.table.DefaultTableModel(
            new Object [][] {
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null}
            },
            new String [] {
                "Title 1", "Title 2", "Title 3", "Title 4"
            }
        ));
        jScrollPane3.setViewportView(FilmsTable);

        SearchFilmsBtn.setText("Search");
        SearchFilmsBtn.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                SearchFilmsBtnActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout jPanel4Layout = new javax.swing.GroupLayout(jPanel4);
        jPanel4.setLayout(jPanel4Layout);
        jPanel4Layout.setHorizontalGroup(
            jPanel4Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel4Layout.createSequentialGroup()
                .addGroup(jPanel4Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addGroup(jPanel4Layout.createSequentialGroup()
                        .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(SearchFieldFilms, javax.swing.GroupLayout.PREFERRED_SIZE, 351, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(SearchFilmsBtn))
                    .addGroup(jPanel4Layout.createSequentialGroup()
                        .addContainerGap(143, Short.MAX_VALUE)
                        .addComponent(jScrollPane3, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addGap(62, 62, 62)
                .addComponent(AddFilmsBtn)
                .addGap(53, 53, 53))
        );
        jPanel4Layout.setVerticalGroup(
            jPanel4Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel4Layout.createSequentialGroup()
                .addGap(20, 20, 20)
                .addGroup(jPanel4Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(SearchFieldFilms, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(SearchFilmsBtn)
                    .addComponent(AddFilmsBtn))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 27, Short.MAX_VALUE)
                .addComponent(jScrollPane3, javax.swing.GroupLayout.PREFERRED_SIZE, 375, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(19, 19, 19))
        );

        javax.swing.GroupLayout FilmLayout = new javax.swing.GroupLayout(Film);
        Film.setLayout(FilmLayout);
        FilmLayout.setHorizontalGroup(
            FilmLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jPanel4, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );
        FilmLayout.setVerticalGroup(
            FilmLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jPanel4, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );

        jTabbedPane1.addTab("Films", Film);

        Report.setBackground(new java.awt.Color(204, 255, 255));

        ReportTable.setModel(new javax.swing.table.DefaultTableModel(
            new Object [][] {
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null}
            },
            new String [] {
                "Title 1", "Title 2", "Title 3", "Title 4"
            }
        ));
        jScrollPane2.setViewportView(ReportTable);

        javax.swing.GroupLayout ReportLayout = new javax.swing.GroupLayout(Report);
        Report.setLayout(ReportLayout);
        ReportLayout.setHorizontalGroup(
            ReportLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(ReportLayout.createSequentialGroup()
                .addGap(148, 148, 148)
                .addComponent(jScrollPane2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(162, Short.MAX_VALUE))
        );
        ReportLayout.setVerticalGroup(
            ReportLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, ReportLayout.createSequentialGroup()
                .addContainerGap(23, Short.MAX_VALUE)
                .addComponent(jScrollPane2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(14, 14, 14))
        );

        jTabbedPane1.addTab("Report", Report);

        Notifications.setBackground(new java.awt.Color(204, 255, 255));

        jButton1.setText("Modify");
        jButton1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton1ActionPerformed(evt);
            }
        });

        CustomerTable.setModel(new javax.swing.table.DefaultTableModel(
            new Object [][] {
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null}
            },
            new String [] {
                "Title 1", "Title 2", "Title 3", "Title 4"
            }
        ));
        jScrollPane4.setViewportView(CustomerTable);

        SearchCustomersBtn.setText("Search");
        SearchCustomersBtn.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                SearchCustomersBtnActionPerformed(evt);
            }
        });

        DroppedSubChk.setText("Dropped Subscription");
        DroppedSubChk.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                DroppedSubChkActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout NotificationsLayout = new javax.swing.GroupLayout(Notifications);
        Notifications.setLayout(NotificationsLayout);
        NotificationsLayout.setHorizontalGroup(
            NotificationsLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(NotificationsLayout.createSequentialGroup()
                .addGap(40, 40, 40)
                .addGroup(NotificationsLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(NotificationsLayout.createSequentialGroup()
                        .addComponent(DroppedSubChk)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(jButton1)
                        .addGap(42, 42, 42))
                    .addGroup(NotificationsLayout.createSequentialGroup()
                        .addGroup(NotificationsLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addGroup(NotificationsLayout.createSequentialGroup()
                                .addComponent(SearchCustomerField, javax.swing.GroupLayout.PREFERRED_SIZE, 533, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(29, 29, 29)
                                .addComponent(SearchCustomersBtn, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                            .addComponent(jScrollPane4, javax.swing.GroupLayout.PREFERRED_SIZE, 693, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addContainerGap(29, Short.MAX_VALUE))))
        );
        NotificationsLayout.setVerticalGroup(
            NotificationsLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(NotificationsLayout.createSequentialGroup()
                .addGap(28, 28, 28)
                .addGroup(NotificationsLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(SearchCustomerField, javax.swing.GroupLayout.PREFERRED_SIZE, 47, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(SearchCustomersBtn, javax.swing.GroupLayout.PREFERRED_SIZE, 47, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(18, 18, 18)
                .addComponent(jScrollPane4, javax.swing.GroupLayout.PREFERRED_SIZE, 326, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGroup(NotificationsLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(NotificationsLayout.createSequentialGroup()
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(jButton1)
                        .addContainerGap())
                    .addGroup(NotificationsLayout.createSequentialGroup()
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(DroppedSubChk)
                        .addContainerGap(13, Short.MAX_VALUE))))
        );

        jTabbedPane1.addTab("Notifications", Notifications);

        javax.swing.GroupLayout jPanel1Layout = new javax.swing.GroupLayout(jPanel1);
        jPanel1.setLayout(jPanel1Layout);
        jPanel1Layout.setHorizontalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 774, Short.MAX_VALUE)
            .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addGroup(jPanel1Layout.createSequentialGroup()
                    .addContainerGap()
                    .addComponent(jTabbedPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 700, Short.MAX_VALUE)
                    .addContainerGap()))
        );
        jPanel1Layout.setVerticalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 537, Short.MAX_VALUE)
            .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addGroup(jPanel1Layout.createSequentialGroup()
                    .addContainerGap()
                    .addComponent(jTabbedPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 500, Short.MAX_VALUE)
                    .addContainerGap()))
        );

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jPanel1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jPanel1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void chkFirstNameActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_chkFirstNameActionPerformed
        try {
            populateStaffTable();
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(GUI.class.getName()).log(Level.SEVERE, null, ex);
        } catch (SQLException ex) {
            Logger.getLogger(GUI.class.getName()).log(Level.SEVERE, null, ex);
        }
    }//GEN-LAST:event_chkFirstNameActionPerformed

    private void chkLastNameActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_chkLastNameActionPerformed
        try {
            populateStaffTable();
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(GUI.class.getName()).log(Level.SEVERE, null, ex);
        } catch (SQLException ex) {
            Logger.getLogger(GUI.class.getName()).log(Level.SEVERE, null, ex);
        }
    }//GEN-LAST:event_chkLastNameActionPerformed

    private void chkAddressActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_chkAddressActionPerformed
        try {
            populateStaffTable();
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(GUI.class.getName()).log(Level.SEVERE, null, ex);
        } catch (SQLException ex) {
            Logger.getLogger(GUI.class.getName()).log(Level.SEVERE, null, ex);
        }
    }//GEN-LAST:event_chkAddressActionPerformed

    private void chkDistrictActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_chkDistrictActionPerformed
        try {
            populateStaffTable();
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(GUI.class.getName()).log(Level.SEVERE, null, ex);
        } catch (SQLException ex) {
            Logger.getLogger(GUI.class.getName()).log(Level.SEVERE, null, ex);
        }
    }//GEN-LAST:event_chkDistrictActionPerformed

    private void chkCityActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_chkCityActionPerformed
       try {
            populateStaffTable();
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(GUI.class.getName()).log(Level.SEVERE, null, ex);
        } catch (SQLException ex) {
            Logger.getLogger(GUI.class.getName()).log(Level.SEVERE, null, ex);
        }
    }//GEN-LAST:event_chkCityActionPerformed

    private void chkPostalActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_chkPostalActionPerformed
        try {
            populateStaffTable();
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(GUI.class.getName()).log(Level.SEVERE, null, ex);
        } catch (SQLException ex) {
            Logger.getLogger(GUI.class.getName()).log(Level.SEVERE, null, ex);
        }
    }//GEN-LAST:event_chkPostalActionPerformed

    private void chkPhoneActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_chkPhoneActionPerformed
       try {
            populateStaffTable();
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(GUI.class.getName()).log(Level.SEVERE, null, ex);
        } catch (SQLException ex) {
            Logger.getLogger(GUI.class.getName()).log(Level.SEVERE, null, ex);
        }
    }//GEN-LAST:event_chkPhoneActionPerformed

    private void chkStoreActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_chkStoreActionPerformed
        try {
            populateStaffTable();
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(GUI.class.getName()).log(Level.SEVERE, null, ex);
        } catch (SQLException ex) {
            Logger.getLogger(GUI.class.getName()).log(Level.SEVERE, null, ex);
        }
    }//GEN-LAST:event_chkStoreActionPerformed

    private void chkActiveActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_chkActiveActionPerformed
       try {
            populateStaffTable();
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(GUI.class.getName()).log(Level.SEVERE, null, ex);
        } catch (SQLException ex) {
            Logger.getLogger(GUI.class.getName()).log(Level.SEVERE, null, ex);
        }
    }//GEN-LAST:event_chkActiveActionPerformed

    private void SearchFilmsBtnActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_SearchFilmsBtnActionPerformed
        try {
            populateFilmsTable();
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(GUI.class.getName()).log(Level.SEVERE, null, ex);
        } catch (SQLException ex) {
            Logger.getLogger(GUI.class.getName()).log(Level.SEVERE, null, ex);
        }
    }//GEN-LAST:event_SearchFilmsBtnActionPerformed

    private void AddFilmsBtnActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_AddFilmsBtnActionPerformed
        AddFilms f = null;
        try {
            f = new AddFilms();
        } catch (IOException ex) {
            Logger.getLogger(GUI.class.getName()).log(Level.SEVERE, null, ex);
        }
        f.setVisible(true);
        this.dispose();
    }//GEN-LAST:event_AddFilmsBtnActionPerformed

    private void SearchCustomersBtnActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_SearchCustomersBtnActionPerformed
        try {
            populateCustomerTable();
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(GUI.class.getName()).log(Level.SEVERE, null, ex);
        } catch (SQLException ex) {
            Logger.getLogger(GUI.class.getName()).log(Level.SEVERE, null, ex);
        }
    }//GEN-LAST:event_SearchCustomersBtnActionPerformed

    private void DroppedSubChkActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_DroppedSubChkActionPerformed
        try {
            populateCustomerTable();
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(GUI.class.getName()).log(Level.SEVERE, null, ex);
        } catch (SQLException ex) {
            Logger.getLogger(GUI.class.getName()).log(Level.SEVERE, null, ex);
        }
    }//GEN-LAST:event_DroppedSubChkActionPerformed

    private void jButton1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton1ActionPerformed
        Customers c = null;
        try {
            c = new Customers();
            c.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        } catch (IOException ex) {
            Logger.getLogger(GUI.class.getName()).log(Level.SEVERE, null, ex);
        }
        c.setVisible(true);
    }//GEN-LAST:event_jButton1ActionPerformed
    
    public static void main(String args[]) throws ClassNotFoundException, SQLException
    {
        java.awt.EventQueue.invokeLater(new Runnable() 
        {
            public void run() {
                try {
                    new GUI().setVisible(true);
                } catch (ClassNotFoundException ex) {
                    Logger.getLogger(GUI.class.getName()).log(Level.SEVERE, null, ex);
                } catch (SQLException ex) {
                    Logger.getLogger(GUI.class.getName()).log(Level.SEVERE, null, ex);
                } catch (IOException ex) {
                    Logger.getLogger(GUI.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JToggleButton AddFilmsBtn;
    private javax.swing.JTable CustomerTable;
    private javax.swing.JCheckBox DroppedSubChk;
    private javax.swing.JPanel Film;
    private javax.swing.JTable FilmsTable;
    private javax.swing.JPanel Notifications;
    private javax.swing.JPanel Report;
    private javax.swing.JTable ReportTable;
    private javax.swing.JTextField SearchCustomerField;
    private javax.swing.JButton SearchCustomersBtn;
    private javax.swing.JTextField SearchFieldFilms;
    private javax.swing.JButton SearchFilmsBtn;
    private javax.swing.JPanel Staff;
    private javax.swing.JTable StaffTable;
    private javax.swing.JCheckBox chkActive;
    private javax.swing.JCheckBox chkAddress;
    private javax.swing.JCheckBox chkCity;
    private javax.swing.JCheckBox chkDistrict;
    private javax.swing.JCheckBox chkFirstName;
    private javax.swing.JCheckBox chkLastName;
    private javax.swing.JCheckBox chkPhone;
    private javax.swing.JCheckBox chkPostal;
    private javax.swing.JCheckBox chkStore;
    private javax.swing.JButton jButton1;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JPanel jPanel3;
    private javax.swing.JPanel jPanel4;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JScrollPane jScrollPane2;
    private javax.swing.JScrollPane jScrollPane3;
    private javax.swing.JScrollPane jScrollPane4;
    private javax.swing.JTabbedPane jTabbedPane1;
    // End of variables declaration//GEN-END:variables

    private void populateStaffTable() throws ClassNotFoundException, SQLException 
    {
        Class.forName("org.mariadb.jdbc.Driver");
        String url = protocol+":mariadb://"+host+":"+port+"/"+dbName;
       
        Connection connection = DriverManager.getConnection(url, username, password );
        
        Statement statement = connection.createStatement();
        ResultSet resultSet = statement.executeQuery("SELECT * FROM staff LIMIT 1000");
        
        ArrayList<String> columns = new ArrayList<>();
        int count = 0;
        if (chkFirstName.isSelected()) 
        {
            columns.add("First Name");
            count++;
        }

        if (chkLastName.isSelected()) {
            columns.add("Last Name");
            count++;
        }
        
        if (chkAddress.isSelected()) 
        {
            columns.add("Address");
            count++;
        }

        if (chkDistrict.isSelected()) {
            columns.add("District");
            count++;
        }
        
        if (chkCity.isSelected()) {
            columns.add("City");
            count++;
        }
        
        if (chkPostal.isSelected()) {
            columns.add("Postal Code");
            count++;
        }
        
        if (chkPhone.isSelected()) {
            columns.add("Phone");
            count++;
        }
        
        if (chkStore.isSelected()) {
            columns.add("Store");
            count++;
        }
        
        if (chkActive.isSelected()) {
            columns.add("Active Status");
            count++;
        }
        if(count != 0)
        {
            Object[][] data = new Object[1000][count];
            int row = 0;
            while (resultSet.next()) 
            {
                count = 0;
                if (chkFirstName.isSelected()) 
                {   
                    
                    data[row][count++] = resultSet.getString("first_name");

                }
                if (chkLastName.isSelected()) 
                {
                    data[row][count++] = resultSet.getString("last_name");
                }

                int address_id = resultSet.getInt("address_id");
                ResultSet resultAddress = statement.executeQuery("SELECT * FROM address WHERE address_id = "+address_id + " LIMIT 1000");
                if (resultAddress.next()) 
                {
                    if (chkAddress.isSelected()) {
                        data[row][count++] = resultAddress.getString("address");
                    }
                    if (chkDistrict.isSelected()) {
                        data[row][count++] = resultAddress.getString("district");
                    }
                    int city_id = resultAddress.getInt("city_id");
                    ResultSet resultCity = statement.executeQuery("SELECT * FROM city WHERE city_id = "+city_id + " LIMIT 1000");
                    if(resultCity.next())
                    {
                        if (chkCity.isSelected()) {
                            data[row][count++] = resultCity.getString("city");
                        }
                    }
                    if (chkPostal.isSelected()) {
                        data[row][count++] = resultAddress.getString("postal_code");
                    }
                    if (chkPhone.isSelected()) {
                        data[row][count++] = resultAddress.getString("phone");
                    }
                }
                if (chkStore.isSelected()) {
                    data[row][count++] = resultSet.getString("store_id");
                }
                if (chkActive.isSelected()) {
                    data[row][count++] = resultSet.getBoolean("active");
                }
                row++;
            }
            String[] columnsArray = columns.toArray(new String[0]);
            DefaultTableModel model = new DefaultTableModel(data,columnsArray);

            StaffTable.setModel(model);
        }
    }

    
    private void populateReportTable() throws ClassNotFoundException, SQLException
    {
        Class.forName("org.mariadb.jdbc.Driver");
        String url = protocol+":mariadb://"+host+":"+port+"/"+dbName;
       
        Connection connection = DriverManager.getConnection(url, username, password );
        
        Statement statement = connection.createStatement();
        

        ResultSet resultSet = statement.executeQuery("SELECT s.store_id, c.name AS genre_name, COUNT(*) AS movie_count "
                + "FROM film f "
                + "JOIN inventory i ON f.film_id = i.film_id "
                + "JOIN film_category fc ON f.film_id = fc.film_id "
                + "JOIN category c ON fc.category_id = c.category_id "
                + "JOIN store s ON i.store_id = s.store_id "
                + "GROUP BY s.store_id, c.name "
                + "ORDER BY s.store_id, movie_count DESC LIMIT 1000;");
       
        
        String[] columns = {"Store" , "Genre" , "Count"};
        Object[][] data = new Object[1000][3];
        int rows = 0;
        while(resultSet.next())
        {
            int store_id = resultSet.getInt("store_id");
            data[rows][0] = store_id;
            
            String genre = resultSet.getString("genre_name");
            data[rows][1] = genre;
            
            int count = resultSet.getInt("movie_count");
            data[rows][2] = count;
            rows++;
        }
        
        

        DefaultTableModel model = new DefaultTableModel(data,columns);

        ReportTable.setModel(model);
    }
    
    
    
    private void populateFilmsTable() throws ClassNotFoundException, SQLException
    {
        Class.forName("org.mariadb.jdbc.Driver");
        String url = protocol+":mariadb://"+host+":"+port+"/"+dbName;
       
        Connection connection = DriverManager.getConnection(url, username, password );
        
        Statement statement = connection.createStatement();
        String searchquery = SearchFieldFilms.getText();
        String sql = "SELECT film.title, category.name AS genre, language.name as language , film.release_year "
                + "FROM `film_category` "
                + "JOIN film ON film.film_id = film_category.film_id "
                + "JOIN category ON film_category.category_id = category.category_id "
                + "JOIN language ON film.language_id = language.language_id ";
        
        if(!searchquery.isEmpty())
        {
            sql+="WHERE film.title LIKE '%"+searchquery+"%' OR category.name LIKE '%"+searchquery+"%' OR language.name LIKE '%"+searchquery+"%' OR film.release_year LIKE '%"+searchquery+"%'";
        }
        
        sql += " LIMIT 1000";
        ResultSet resultSet = statement.executeQuery(sql);
        
        String columns[] = {"Title" , "Genre" , "Language" , "Release Year"};
        Object[][] data = new Object[1000][4];
        int rows = 0;
        while(resultSet.next())
        {
            data[rows][0] = resultSet.getString("title");
            data[rows][1] = resultSet.getString("genre");
            data[rows][2] = resultSet.getString("language");
            data[rows][3] = resultSet.getString("release_year");
            rows++;
        }
        
        DefaultTableModel model = new DefaultTableModel(data,columns);
        FilmsTable.setModel(model);
    }
    
    
    private void populateCustomerTable() throws ClassNotFoundException, SQLException
    {
        Class.forName("org.mariadb.jdbc.Driver");
        String url = protocol+":mariadb://"+host+":"+port+"/"+dbName;
       
        Connection connection = DriverManager.getConnection(url, username, password );
        
        Statement statement = connection.createStatement();
        String sql = "SELECT store_id,first_name,last_name,email,address,district,phone,active FROM `customer` " +
        "INNER JOIN address ON customer.address_id = address.address_id ";
        
        if(DroppedSubChk.isSelected())
        {
            sql+="WHERE active = 0 ";
        }

                
        sql +="AND (first_name LIKE '%"+SearchCustomerField.getText()+"%' "
                + "OR last_name LIKE '%"+SearchCustomerField.getText()+"%' "
                + "OR email LIKE '%"+SearchCustomerField.getText()+"%' "
                + "OR address LIKE '%"+SearchCustomerField.getText()+"%' "
                + "OR district LIKE '%"+SearchCustomerField.getText()+"%' "
                + "OR phone LIKE '%"+SearchCustomerField.getText()+"%' )"
                + " LIMIT 1000";
        
        ResultSet resultSet = statement.executeQuery(sql);
        String columns[] = {"Store" ,"FirstName" , "LastName" , "Email" , "address", "District" , "Phone" , "Subscription"};
        Object[][] data = new Object[1000][8];
        int rows = 0;
        while(resultSet.next())
        {
            data[rows][0] = resultSet.getString("store_id");
            data[rows][1] = resultSet.getString("first_name");
            data[rows][2] = resultSet.getString("last_name");
            data[rows][3] = resultSet.getString("email");
            data[rows][4] = resultSet.getString("address");
            data[rows][5] = resultSet.getString("district");
            data[rows][6] = resultSet.getString("phone");
            data[rows][7] = resultSet.getString("active");
            rows++;
        }
        DefaultTableModel model = new DefaultTableModel(data,columns);
        CustomerTable.setModel(model);
    }
}

